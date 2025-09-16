#pragma once
// 核心概念定义 - 借鉴wxUI的类型安全设计

#include <concepts>
#include <type_traits>
#include <functional>
#include <string>

struct lv_obj_t; // 前向声明

namespace lvgl_modern::concepts {

// 基础概念：可绘制对象
template<typename T>
concept Drawable = requires(T obj, lv_obj_t* parent) {
    { obj.createImpl(parent) } -> std::convertible_to<lv_obj_t*>;
};

// 可样式化对象 - 简化为只检查是否有样式相关方法
template<typename T>
concept Styleable = requires(T obj) {
    obj.size(100, 100);
    obj.position(0, 0);
};

// 可布局对象
template<typename T>
concept Layoutable = requires(T obj, lv_obj_t* parent) {
    obj.createAndAdd(parent);
};

// 容器概念
template<typename T>
concept Container = Drawable<T>;

// 事件处理器概念
template<typename T>
concept EventHandler = requires(T handler) {
    handler();
} || requires(T handler, int value) {
    handler(value);
} || requires(T handler, const std::string& text) {
    handler(text);
};

// 可观察对象概念
template<typename T>
concept Observable = requires(T obs) {
    typename T::ValueType;
    { obs.get() } -> std::convertible_to<typename T::ValueType>;
    obs.set(std::declval<typename T::ValueType>());
};

// 响应式绑定概念
template<typename T, typename U>
concept BindableTo = requires(T target, U source) {
    target.bindTo(source);
};

// 线程安全概念
template<typename T>
concept ThreadSafe = requires(T obj) {
    obj.postToMainThread(std::declval<std::function<void()>>());
};

// 生命周期管理概念
template<typename T>
concept LifecycleManaged = requires(T obj) {
    { obj.isAlive() } -> std::convertible_to<bool>;
};

// 延迟构造概念
template<typename T>
concept LazyConstructible = requires(T obj) {
    { obj.isAlive() } -> std::convertible_to<bool>;
};

// 方法链概念
template<typename T>
concept Chainable = requires(T obj) {
    { obj.self() } -> std::same_as<T&>;
};

// 组合概念：完整的UI组件 - 简化约束
template<typename T>
concept UIComponent = Drawable<T> && Styleable<T> && Chainable<T>;

// 布局组件概念
template<typename T>
concept LayoutComponent = Container<T> && UIComponent<T>;

} // namespace lvgl_modern::concepts