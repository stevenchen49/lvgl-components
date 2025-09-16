#pragma once
// 布局容器 - 借鉴wxUI的声明式布局设计

#include "../core/widget_base.hpp"
#include "../core/concepts.hpp"
#include <mock_lvgl/lvgl.h>
#include <vector>
#include <memory>
#include <tuple>

namespace lvgl_modern::layouts {

// 类型擦除的基类
class WidgetInterface {
public:
    virtual ~WidgetInterface() = default;
    virtual void createAndAdd(lv_obj_t* parent) = 0;
    virtual void destroy() = 0;
    virtual bool isAlive() const = 0;
};

// 类型擦除的包装器
template<typename T>
class WidgetWrapper : public WidgetInterface {
public:
    explicit WidgetWrapper(T widget) : widget_(std::move(widget)) {}
    
    void createAndAdd(lv_obj_t* parent) override {
        widget_.createAndAdd(parent);
    }
    
    void destroy() override {
        widget_.destroy();
    }
    
    bool isAlive() const override {
        return widget_.isAlive();
    }
    
private:
    T widget_;
};

// 基础容器类
template<typename Derived>
class ContainerBase : public core::WidgetBase<Derived> {
public:
    // 添加子控件 - 使用类型擦除
    template<typename Child>
    auto& add(Child&& child) {
        children_.emplace_back(std::make_unique<WidgetWrapper<std::decay_t<Child>>>(
            std::forward<Child>(child)));
        
        // 如果容器已构造，立即创建子控件
        if (this->native()) {
            children_.back()->createAndAdd(this->native());
        }
        
        return this->self();
    }
    
    // 批量添加子控件 - 支持初始化列表语法
    template<typename... Children>
    auto& children(Children&&... children) {
        (add(std::forward<Children>(children)), ...);
        return this->self();
    }
    
    // 间距设置
    auto& spacing(int space) {
        spacing_ = space;
        if (this->native()) {
            applySpacing();
        }
        return this->self();
    }
    
    // 内边距设置
    auto& padding(int pad) {
        padding_ = pad;
        if (this->native()) {
            applyPadding();
        }
        return this->self();
    }
    
    auto& padding(int top, int right, int bottom, int left) {
        padding_top_ = top;
        padding_right_ = right;
        padding_bottom_ = bottom;
        padding_left_ = left;
        if (this->native()) {
            applyPadding();
        }
        return this->self();
    }
    
    // 对齐方式设置
    auto& align(lv_flex_align_t main, lv_flex_align_t cross = LV_FLEX_ALIGN_START) {
        main_align_ = main;
        cross_align_ = cross;
        if (this->native()) {
            applyAlignment();
        }
        return this->self();
    }
    
    // 居中对齐快捷方法
    auto& center() {
        return align(LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    }
    
    // 适应到父容器
    void fitTo(lv_obj_t* parent) {
        this->createAndAdd(parent);
    }
    
protected:
    void onCreate() override {
        core::WidgetBase<Derived>::onCreate();
        
        // 设置布局属性
        applyLayoutProperties();
        
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
        
        core::WidgetBase<Derived>::onDestroy();
    }
    
    virtual void applyLayoutProperties() {
        if (this->native()) {
            applySpacing();
            applyPadding();
            applyAlignment();
        }
    }
    
    virtual void applySpacing() {
        if (spacing_ > 0) {
            std::cout << "[Container] Applied spacing: " << spacing_ << std::endl;
            // 在实际LVGL中设置间距
        }
    }
    
    virtual void applyPadding() {
        if (padding_ > 0 || padding_top_ >= 0) {
            std::cout << "[Container] Applied padding" << std::endl;
            // 在实际LVGL中设置内边距
        }
    }
    
    virtual void applyAlignment() {
        if (this->native()) {
            lv_obj_set_flex_align(this->native(), main_align_, cross_align_, LV_FLEX_ALIGN_START);
        }
    }
    
    // 子控件存储 - 使用类型擦除
    std::vector<std::unique_ptr<WidgetInterface>> children_;
    
    // 布局属性
    int spacing_ = 0;
    int padding_ = 0;
    int padding_top_ = -1, padding_right_ = -1, padding_bottom_ = -1, padding_left_ = -1;
    lv_flex_align_t main_align_ = LV_FLEX_ALIGN_START;
    lv_flex_align_t cross_align_ = LV_FLEX_ALIGN_START;
};

// 垂直布局容器
class VBox : public ContainerBase<VBox> {
public:
    // 支持初始化列表构造 - 简化约束
    template<typename... Children>
    VBox(Children&&... children) {
        (add(std::forward<Children>(children)), ...);
    }
    
    VBox() = default;
    
    lv_obj_t* createImpl(lv_obj_t* parent) override {
        auto* container = lv_obj_create(parent);
        lv_obj_set_flex_flow(container, LV_FLEX_FLOW_COLUMN);
        std::cout << "[VBox] Created vertical container" << std::endl;
        return container;
    }
    
    // 静态工厂方法
    template<typename... Children>
    static auto create(Children&&... children) {
        return VBox(std::forward<Children>(children)...);
    }
};

// 水平布局容器
class HBox : public ContainerBase<HBox> {
public:
    // 支持初始化列表构造 - 简化约束
    template<typename... Children>
    HBox(Children&&... children) {
        (add(std::forward<Children>(children)), ...);
    }
    
    HBox() = default;
    
    lv_obj_t* createImpl(lv_obj_t* parent) override {
        auto* container = lv_obj_create(parent);
        lv_obj_set_flex_flow(container, LV_FLEX_FLOW_ROW);
        std::cout << "[HBox] Created horizontal container" << std::endl;
        return container;
    }
    
    // 静态工厂方法
    template<typename... Children>
    static auto create(Children&&... children) {
        return HBox(std::forward<Children>(children)...);
    }
};

// 网格布局容器
class Grid : public ContainerBase<Grid> {
public:
    Grid() = default;
    Grid(int columns, int rows) : columns_(columns), rows_(rows) {}
    
    template<typename... Children>
    Grid(int columns, int rows, Children&&... children) 
        : columns_(columns), rows_(rows) {
        (add(std::forward<Children>(children)), ...);
    }
    
    lv_obj_t* createImpl(lv_obj_t* parent) override {
        auto* container = lv_obj_create(parent);
        // 在实际LVGL中设置网格布局
        std::cout << "[Grid] Created grid container (" << columns_ << "x" << rows_ << ")" << std::endl;
        return container;
    }
    
    auto& gridSize(int columns, int rows) {
        columns_ = columns;
        rows_ = rows;
        return self();
    }
    
    // 静态工厂方法
    template<typename... Children>
    static auto create(int columns, int rows, Children&&... children) {
        return Grid(columns, rows, std::forward<Children>(children)...);
    }
    
private:
    int columns_ = 1;
    int rows_ = 1;
};

// 滚动容器
class ScrollView : public ContainerBase<ScrollView> {
public:
    ScrollView() = default;
    
    template<typename... Children>
    ScrollView(Children&&... children) {
        (add(std::forward<Children>(children)), ...);
    }
    
    lv_obj_t* createImpl(lv_obj_t* parent) override {
        auto* container = lv_obj_create(parent);
        // 在实际LVGL中启用滚动
        std::cout << "[ScrollView] Created scrollable container" << std::endl;
        return container;
    }
    
    auto& scrollDirection(bool horizontal, bool vertical) {
        scroll_horizontal_ = horizontal;
        scroll_vertical_ = vertical;
        if (native()) {
            // 在实际LVGL中设置滚动方向
            std::cout << "[ScrollView] Scroll direction set: H=" << horizontal << ", V=" << vertical << std::endl;
        }
        return self();
    }
    
    // 静态工厂方法
    template<typename... Children>
    static auto create(Children&&... children) {
        return ScrollView(std::forward<Children>(children)...);
    }
    
private:
    bool scroll_horizontal_ = false;
    bool scroll_vertical_ = true;
};

// 便利的工厂函数
template<typename... Children>
auto createVBox(Children&&... children) {
    return VBox(std::forward<Children>(children)...);
}

template<typename... Children>
auto createHBox(Children&&... children) {
    return HBox(std::forward<Children>(children)...);
}

template<typename... Children>
auto createGrid(int columns, int rows, Children&&... children) {
    return Grid(columns, rows, std::forward<Children>(children)...);
}

} // namespace lvgl_modern::layouts