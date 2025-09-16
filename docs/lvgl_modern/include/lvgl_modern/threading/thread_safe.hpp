#pragma once
// 线程安全模块 - 解决LVGL的非线程安全问题

#include <functional>
#include <queue>
#include <mutex>
#include <shared_mutex>
#include <condition_variable>
#include <thread>
#include <atomic>
#include <future>
#include <iostream>

namespace lvgl_modern::threading {

// 线程安全的任务队列
class TaskQueue {
public:
    using Task = std::function<void()>;
    
    void push(Task task) {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            tasks_.push(std::move(task));
        }
        condition_.notify_one();
    }
    
    bool tryPop(Task& task) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (tasks_.empty()) {
            return false;
        }
        task = std::move(tasks_.front());
        tasks_.pop();
        return true;
    }
    
    void waitAndPop(Task& task) {
        std::unique_lock<std::mutex> lock(mutex_);
        condition_.wait(lock, [this] { return !tasks_.empty() || shutdown_; });
        
        if (shutdown_ && tasks_.empty()) {
            throw std::runtime_error("TaskQueue is shutting down");
        }
        
        task = std::move(tasks_.front());
        tasks_.pop();
    }
    
    void shutdown() {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            shutdown_ = true;
        }
        condition_.notify_all();
    }
    
    size_t size() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return tasks_.size();
    }
    
private:
    mutable std::mutex mutex_;
    std::queue<Task> tasks_;
    std::condition_variable condition_;
    std::atomic<bool> shutdown_{false};
};

// 主线程任务调度器
class MainThreadScheduler {
public:
    static MainThreadScheduler& instance() {
        static MainThreadScheduler scheduler;
        return scheduler;
    }
    
    // 从任意线程投递任务到主线程
    void post(std::function<void()> task) {
        task_queue_.push(std::move(task));
    }
    
    // 从任意线程投递任务并等待结果
    template<typename Func, typename... Args>
    auto postAndWait(Func&& func, Args&&... args) -> std::invoke_result_t<Func, Args...> {
        using ReturnType = std::invoke_result_t<Func, Args...>;
        
        auto promise = std::make_shared<std::promise<ReturnType>>();
        auto future = promise->get_future();
        
        post([promise, func = std::forward<Func>(func), args...]() mutable {
            try {
                if constexpr (std::is_void_v<ReturnType>) {
                    func(args...);
                    promise->set_value();
                } else {
                    auto result = func(args...);
                    promise->set_value(std::move(result));
                }
            } catch (...) {
                promise->set_exception(std::current_exception());
            }
        });
        
        return future.get();
    }
    
    // 处理主线程任务队列（应在主线程的事件循环中调用）
    void processTasks() {
        TaskQueue::Task task;
        while (task_queue_.tryPop(task)) {
            try {
                task();
            } catch (const std::exception& e) {
                std::cerr << "[ThreadSafe] Task execution failed: " << e.what() << std::endl;
            }
        }
    }
    
    // 设置主线程ID
    void setMainThread() {
        main_thread_id_ = std::this_thread::get_id();
        std::cout << "[ThreadSafe] Main thread ID set" << std::endl;
    }
    
    // 检查是否在主线程
    bool isMainThread() const {
        return std::this_thread::get_id() == main_thread_id_;
    }
    
    void shutdown() {
        task_queue_.shutdown();
    }
    
private:
    TaskQueue task_queue_;
    std::thread::id main_thread_id_;
    
    MainThreadScheduler() = default;
};

// 线程安全的UI操作接口
class ThreadSafe {
public:
    // 投递任务到主线程
    static void post(std::function<void()> task) {
        MainThreadScheduler::instance().post(std::move(task));
    }
    
    // 投递任务并等待结果
    template<typename Func, typename... Args>
    static auto postAndWait(Func&& func, Args&&... args) {
        return MainThreadScheduler::instance().postAndWait(
            std::forward<Func>(func), std::forward<Args>(args)...);
    }
    
    // 如果在主线程则直接执行，否则投递到主线程
    static void execute(std::function<void()> task) {
        if (MainThreadScheduler::instance().isMainThread()) {
            task();
        } else {
            post(std::move(task));
        }
    }
    
    // 处理任务队列
    static void processTasks() {
        MainThreadScheduler::instance().processTasks();
    }
    
    // 初始化（设置主线程）
    static void initialize() {
        MainThreadScheduler::instance().setMainThread();
    }
    
    // 清理
    static void shutdown() {
        MainThreadScheduler::instance().shutdown();
    }
};

// RAII线程安全守护
class ThreadGuard {
public:
    ThreadGuard() {
        ThreadSafe::initialize();
    }
    
    ~ThreadGuard() {
        ThreadSafe::shutdown();
    }
    
    // 禁止拷贝和移动
    ThreadGuard(const ThreadGuard&) = delete;
    ThreadGuard& operator=(const ThreadGuard&) = delete;
    ThreadGuard(ThreadGuard&&) = delete;
    ThreadGuard& operator=(ThreadGuard&&) = delete;
};

// 线程安全的属性访问器
template<typename T>
class ThreadSafeProperty {
public:
    ThreadSafeProperty() = default;
    explicit ThreadSafeProperty(T value) : value_(std::move(value)) {}
    
    // 线程安全的读取
    T get() const {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        return value_;
    }
    
    // 线程安全的设置
    void set(T value) {
        std::unique_lock<std::shared_mutex> lock(mutex_);
        value_ = std::move(value);
    }
    
    // 线程安全的修改
    template<typename Func>
    void modify(Func&& func) {
        std::unique_lock<std::shared_mutex> lock(mutex_);
        func(value_);
    }
    
    // 原子交换
    T exchange(T new_value) {
        std::unique_lock<std::shared_mutex> lock(mutex_);
        T old_value = std::move(value_);
        value_ = std::move(new_value);
        return old_value;
    }
    
private:
    mutable std::shared_mutex mutex_;
    T value_;
};

} // namespace lvgl_modern::threading