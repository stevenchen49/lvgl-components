#pragma once
// 控件基类 - 借鉴wxUI的CRTP设计模式

#include "concepts.hpp"
#include "../threading/thread_safe.hpp"
#include "../reactive/observable.hpp"
#include <mock_lvgl/lvgl.h>
#include <memory>
#include <functional>
#include <string>

namespace lvgl_modern::core {

// CRTP基类 - 类似wxUI的WidgetDetails
template<typename Derived, typename LVGLType = lv_obj_t>
class WidgetBase {
public:
    using SelfType = Derived;
    using NativeType = LVGLType;
    
    // 构造函数
    WidgetBase() = default;
    
    // 移动构造和赋值
    WidgetBase(WidgetBase&&) = default;
    WidgetBase& operator=(WidgetBase&&) = default;
    
    // 禁止拷贝
    WidgetBase(const WidgetBase&) = delete;
    WidgetBase& operator=(const WidgetBase&) = delete;
    
    // 虚析构函数
    virtual ~WidgetBase() = default;
    
    // CRTP自引用 - 支持方法链
    auto& self() { return static_cast<Derived&>(*this); }
    const auto& self() const { return static_cast<const Derived&>(*this); }
    
    // 延迟构造接口
    virtual lv_obj_t* createImpl(lv_obj_t* parent) = 0;
    
    // 创建并添加到父容器
    void createAndAdd(lv_obj_t* parent) {
        if (!native_obj_) {
            native_obj_ = createImpl(parent);
            onCreate();
            applyStyle();
            bindEvents();
        }
    }
    
    // 获取原生LVGL对象
    lv_obj_t* native() const { return native_obj_; }
    
    // 生命周期管理
    bool isAlive() const { return native_obj_ != nullptr; }
    
    void destroy() {
        if (native_obj_) {
            onDestroy();
            native_obj_ = nullptr; // LVGL会自动清理内存
        }
    }
    
    // 样式设置 - 方法链支持
    template<typename... Args>
    auto& size(Args&&... args) {
        size_setter_ = [args...](lv_obj_t* obj) {
            lv_obj_set_size(obj, args...);
        };
        if (native_obj_) size_setter_(native_obj_);
        return self();
    }
    
    auto& position(lv_coord_t x, lv_coord_t y) {
        pos_setter_ = [x, y](lv_obj_t* obj) {
            lv_obj_set_pos(obj, x, y);
        };
        if (native_obj_) pos_setter_(native_obj_);
        return self();
    }
    
    // 线程安全的属性设置
    template<typename Func>
    auto& threadSafe(Func&& func) {
        threading::ThreadSafe::post([this, func = std::forward<Func>(func)]() {
            if (native_obj_) {
                func(native_obj_);
            }
        });
        return self();
    }
    
protected:
    // 生命周期钩子
    virtual void onCreate() {
        std::cout << "[WidgetBase] " << typeid(Derived).name() << " created" << std::endl;
    }
    
    virtual void onDestroy() {
        std::cout << "[WidgetBase] " << typeid(Derived).name() << " destroyed" << std::endl;
    }
    
    // 样式应用 - 改为 public 以满足概念约束
public:
    virtual void applyStyle() {
        if (native_obj_) {
            if (size_setter_) size_setter_(native_obj_);
            if (pos_setter_) pos_setter_(native_obj_);
        }
    }
    
protected:
    // 事件绑定
    virtual void bindEvents() {
        // 子类重写以绑定特定事件
    }
    
private:
    lv_obj_t* native_obj_ = nullptr;
    std::function<void(lv_obj_t*)> size_setter_;
    std::function<void(lv_obj_t*)> pos_setter_;
};

// 容器基类
template<typename Derived>
class ContainerBase : public WidgetBase<Derived> {
public:
    using ChildType = std::unique_ptr<WidgetBase<WidgetBase<Derived>>>;
    
    // 添加子控件 - 简化约束
    template<typename Child>
    auto& addChild(Child&& child) {
        // 使用类型擦除存储不同类型的子控件
        children_.emplace_back(std::make_unique<Child>(std::forward<Child>(child)));
        
        // 如果容器已构造，立即创建子控件
        if (this->native()) {
            children_.back()->createAndAdd(this->native());
        }
        
        return this->self();
    }
    
    // 批量添加子控件
    template<typename... Children>
    auto& children(Children&&... children) {
        (addChild(std::forward<Children>(children)), ...);
        return this->self();
    }
    
protected:
    void onCreate() override {
        WidgetBase<Derived>::onCreate();
        
        // 创建所有子控件
        for (auto& child : children_) {
            child->createAndAdd(this->native());
        }
    }
    
    void onDestroy() override {
        // 销毁所有子控件
        for (auto& child : children_) {
            child->destroy();
        }
        children_.clear();
        
        WidgetBase<Derived>::onDestroy();
    }
    
private:
    std::vector<std::unique_ptr<WidgetBase<WidgetBase<Derived>>>> children_;
};

// 代理类 - 用于运行时访问
template<typename WidgetType>
class WidgetProxy {
public:
    WidgetProxy() = default;
    
    void bind(WidgetType* widget) {
        widget_ = widget;
    }
    
    WidgetType* operator->() const {
        if (!widget_) {
            throw std::runtime_error("Proxy not bound to widget");
        }
        return widget_;
    }
    
    WidgetType& operator*() const {
        if (!widget_) {
            throw std::runtime_error("Proxy not bound to widget");
        }
        return *widget_;
    }
    
    bool isBound() const { return widget_ != nullptr; }
    
private:
    WidgetType* widget_ = nullptr;
};

} // namespace lvgl_modern::core