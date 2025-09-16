#pragma once
// 响应式编程模块 - 实现数据驱动的UI更新

#include "../threading/thread_safe.hpp"
#include <functional>
#include <vector>
#include <memory>
#include <mutex>
#include <shared_mutex>
#include <algorithm>
#include <type_traits>
#include <chrono>
#include <thread>
#include <atomic>

namespace lvgl_modern::reactive {

// 前向声明
template<typename T> class Observable;
template<typename T> class ObservableProperty;

// 观察者接口
template<typename T>
class Observer {
public:
    virtual ~Observer() = default;
    virtual void onNext(const T& value) = 0;
    virtual void onError(const std::exception& error) {}
    virtual void onCompleted() {}
};

// 函数式观察者
template<typename T>
class FunctionObserver : public Observer<T> {
public:
    using OnNextFunc = std::function<void(const T&)>;
    using OnErrorFunc = std::function<void(const std::exception&)>;
    using OnCompletedFunc = std::function<void()>;
    
    explicit FunctionObserver(OnNextFunc onNext, 
                             OnErrorFunc onError = nullptr,
                             OnCompletedFunc onCompleted = nullptr)
        : onNext_(std::move(onNext))
        , onError_(std::move(onError))
        , onCompleted_(std::move(onCompleted)) {}
    
    void onNext(const T& value) override {
        if (onNext_) onNext_(value);
    }
    
    void onError(const std::exception& error) override {
        if (onError_) onError_(error);
    }
    
    void onCompleted() override {
        if (onCompleted_) onCompleted_();
    }
    
private:
    OnNextFunc onNext_;
    OnErrorFunc onError_;
    OnCompletedFunc onCompleted_;
};

// 可观察对象
template<typename T>
class Observable {
public:
    using ValueType = T;
    using ObserverPtr = std::shared_ptr<Observer<T>>;
    
    // 构造函数
    Observable() = default;
    explicit Observable(T initial_value) : value_(std::move(initial_value)) {}
    
    // 移动构造和赋值
    Observable(Observable&& other) noexcept 
        : value_(std::move(other.value_))
        , observers_(std::move(other.observers_)) {}
    
    Observable& operator=(Observable&& other) noexcept {
        if (this != &other) {
            std::unique_lock<std::shared_mutex> lock1(mutex_, std::defer_lock);
            std::unique_lock<std::shared_mutex> lock2(other.mutex_, std::defer_lock);
            std::lock(lock1, lock2);
            
            value_ = std::move(other.value_);
            observers_ = std::move(other.observers_);
        }
        return *this;
    }
    
    // 禁止拷贝
    Observable(const Observable&) = delete;
    Observable& operator=(const Observable&) = delete;
    
    // 获取当前值
    T get() const {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        return value_;
    }
    
    // 设置新值并通知观察者
    void set(T new_value) {
        {
            std::unique_lock<std::shared_mutex> lock(mutex_);
            if (value_ == new_value) return; // 值未改变
            value_ = std::move(new_value);
        }
        
        notifyObservers(value_);
    }
    
    // 订阅观察者 - 添加 const 版本
    void subscribe(std::function<void(const T&)> onNext) const {
        auto observer = std::make_shared<FunctionObserver<T>>(std::move(onNext));
        subscribe(observer);
    }
    
    void subscribe(ObserverPtr observer) const {
        std::unique_lock<std::shared_mutex> lock(mutex_);
        observers_.push_back(observer);
        
        // 立即通知新观察者当前值
        threading::ThreadSafe::post([observer, value = value_]() {
            observer->onNext(value);
        });
    }
    
    // 取消订阅
    void unsubscribe(ObserverPtr observer) {
        std::unique_lock<std::shared_mutex> lock(mutex_);
        observers_.erase(
            std::remove(observers_.begin(), observers_.end(), observer),
            observers_.end()
        );
    }
    
    // 映射操作 - 创建新的Observable
    template<typename Func>
    auto map(Func&& func) const -> Observable<std::invoke_result_t<Func, T>> {
        using ResultType = std::invoke_result_t<Func, T>;
        auto result = std::make_shared<Observable<ResultType>>();
        
        // 订阅源Observable
        subscribe([result, func = std::forward<Func>(func)](const T& value) mutable {
            try {
                auto mapped_value = func(value);
                result->set(std::move(mapped_value));
            } catch (const std::exception& e) {
                result->notifyError(e);
            }
        });
        
        return std::move(*result);
    }
    
    // 过滤操作
    template<typename Predicate>
    Observable<T> filter(Predicate&& pred) const {
        auto result = std::make_shared<Observable<T>>();
        
        subscribe([result, pred = std::forward<Predicate>(pred)](const T& value) mutable {
            if (pred(value)) {
                result->set(value);
            }
        });
        
        return std::move(*result);
    }
    
    // 组合操作 - 将两个Observable组合
    template<typename U, typename Func>
    auto combineWith(const Observable<U>& other, Func&& func) const
        -> Observable<std::invoke_result_t<Func, T, U>> {
        using ResultType = std::invoke_result_t<Func, T, U>;
        auto result = std::make_shared<Observable<ResultType>>();
        
        auto combiner = [result, func = std::forward<Func>(func)]
                       (const T& t_val, const U& u_val) mutable {
            try {
                auto combined = func(t_val, u_val);
                result->set(std::move(combined));
            } catch (const std::exception& e) {
                result->notifyError(e);
            }
        };
        
        // 订阅两个源Observable
        subscribe([combiner, &other](const T& value) {
            combiner(value, other.get());
        });
        
        other.subscribe([combiner, this](const U& value) {
            combiner(this->get(), value);
        });
        
        return std::move(*result);
    }
    
    // 防抖动操作
    Observable<T> debounce(std::chrono::milliseconds delay) const {
        auto result = std::make_shared<Observable<T>>();
        auto timer = std::make_shared<std::atomic<bool>>(false);
        
        subscribe([result, delay, timer](const T& value) mutable {
            timer->store(true);
            
            std::thread([result, value, delay, timer]() {
                std::this_thread::sleep_for(delay);
                if (timer->exchange(false)) {
                    result->set(value);
                }
            }).detach();
        });
        
        return std::move(*result);
    }
    
    // 错误通知
    void notifyError(const std::exception& error) const {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        for (auto& observer : observers_) {
            if (auto obs = observer.lock()) {
                threading::ThreadSafe::post([obs, error]() {
                    obs->onError(error);
                });
            }
        }
    }
    
    // 完成通知
    void complete() {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        for (auto& observer : observers_) {
            if (auto obs = observer.lock()) {
                threading::ThreadSafe::post([obs]() {
                    obs->onCompleted();
                });
            }
        }
        observers_.clear();
    }
    
private:
    void notifyObservers(const T& value) const {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        
        // 清理失效的观察者
        observers_.erase(
            std::remove_if(observers_.begin(), observers_.end(),
                          [](const std::weak_ptr<Observer<T>>& obs) {
                              return obs.expired();
                          }),
            observers_.end()
        );
        
        // 通知所有观察者
        for (auto& observer : observers_) {
            if (auto obs = observer.lock()) {
                threading::ThreadSafe::post([obs, value]() {
                    obs->onNext(value);
                });
            }
        }
    }
    
    mutable std::shared_mutex mutex_;
    T value_{};
    mutable std::vector<std::weak_ptr<Observer<T>>> observers_;
};

// 可观察属性 - 用于UI控件的属性绑定
template<typename T>
class ObservableProperty : public Observable<T> {
public:
    using Observable<T>::Observable;
    
    // 重载赋值操作符
    ObservableProperty& operator=(const T& value) {
        this->set(value);
        return *this;
    }
    
    ObservableProperty& operator=(T&& value) {
        this->set(std::move(value));
        return *this;
    }
    
    // 重载转换操作符
    operator T() const {
        return this->get();
    }
    
    // 算术操作符重载
    template<typename U>
    ObservableProperty& operator+=(const U& value) {
        this->set(this->get() + value);
        return *this;
    }
    
    template<typename U>
    ObservableProperty& operator-=(const U& value) {
        this->set(this->get() - value);
        return *this;
    }
    
    // 前置递增/递减
    ObservableProperty& operator++() {
        this->set(this->get() + 1);
        return *this;
    }
    
    ObservableProperty& operator--() {
        this->set(this->get() - 1);
        return *this;
    }
    
    // 后置递增/递减
    T operator++(int) {
        T old_value = this->get();
        this->set(old_value + 1);
        return old_value;
    }
    
    T operator--(int) {
        T old_value = this->get();
        this->set(old_value - 1);
        return old_value;
    }
};

// 工厂函数
template<typename T>
auto makeObservable(T initial_value = T{}) {
    return Observable<T>(std::move(initial_value));
}

template<typename T>
auto makeProperty(T initial_value = T{}) {
    return ObservableProperty<T>(std::move(initial_value));
}

} // namespace lvgl_modern::reactive