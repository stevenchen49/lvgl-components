#pragma once
// Button控件 - 支持事件处理和响应式编程

#include "../core/widget_base.hpp"
#include "../reactive/observable.hpp"
#include <mock_lvgl/lvgl.h>
#include <functional>
#include <string>

namespace lvgl_modern::widgets {

class Button : public core::WidgetBase<Button> {
public:
    using Proxy = core::WidgetProxy<Button>;
    using ClickHandler = std::function<void()>;
    
    // 构造函数
    Button() = default;
    explicit Button(std::string text) : text_(std::move(text)) {}
    
    // 延迟构造实现
    lv_obj_t* createImpl(lv_obj_t* parent) override {
        auto* btn = lv_btn_create(parent);
        
        // 创建按钮标签
        if (!text_.empty()) {
            auto* label = lv_label_create(btn);
            lv_label_set_text(label, text_.c_str());
        }
        
        return btn;
    }
    
    // 文本设置
    auto& text(std::string new_text) {
        text_ = std::move(new_text);
        if (native()) {
            threading::ThreadSafe::execute([this]() {
                // 在实际LVGL中需要找到子标签并设置文本
                std::cout << "[Button] Text updated to: " << text_ << std::endl;
            });
        }
        return self();
    }
    
    // 点击事件绑定
    auto& onClick(ClickHandler handler) {
        click_handler_ = std::move(handler);
        if (native()) {
            bindClickEvent();
        }
        return self();
    }
    
    // 启用/禁用
    auto& enabled(bool enable) {
        enabled_ = enable;
        if (native()) {
            threading::ThreadSafe::execute([this, enable]() {
                // 在实际LVGL中设置控件状态
                std::cout << "[Button] " << (enable ? "Enabled" : "Disabled") << std::endl;
            });
        }
        return self();
    }
    
    // 响应式启用状态绑定
    template<typename ObservableType>
    auto& bindEnabled(const ObservableType& observable) {
        observable.subscribe([this](bool enable) {
            enabled(enable);
        });
        return self();
    }
    
    // 响应式文本绑定
    template<typename ObservableType>
    auto& bindText(const ObservableType& observable) {
        observable.subscribe([this](const auto& value) {
            if constexpr (std::is_convertible_v<decltype(value), std::string>) {
                text(std::string(value));
            } else {
                text(std::to_string(value));
            }
        });
        return self();
    }
    
    // 模拟点击（用于测试）
    void simulateClick() {
        if (click_handler_ && enabled_) {
            std::cout << "[Button] Simulating click on: " << text_ << std::endl;
            threading::ThreadSafe::execute([this]() {
                click_handler_();
            });
        }
    }
    
    // 代理绑定
    auto& withProxy(Proxy& proxy) {
        proxy.bind(this);
        return self();
    }
    
    // 静态工厂方法
    static std::unique_ptr<Button> create(std::string text = "") {
        return std::make_unique<Button>(std::move(text));
    }
    
    // 获取属性
    const std::string& getText() const { return text_; }
    bool isEnabled() const { return enabled_; }
    
protected:
    void bindEvents() override {
        if (click_handler_) {
            bindClickEvent();
        }
    }
    
private:
    void bindClickEvent() {
        if (native() && click_handler_) {
            // 在实际LVGL中绑定点击事件
            lv_obj_add_event_cb(native(), 
                [](lv_event_t* e) {
                    auto* button = static_cast<Button*>(e->user_data);
                    if (button && button->click_handler_ && button->enabled_) {
                        button->click_handler_();
                    }
                }, 
                LV_EVENT_CLICKED, this);
        }
    }
    
    std::string text_;
    ClickHandler click_handler_;
    bool enabled_ = true;
};

// 便利的工厂函数
inline auto createButton(std::string text = "") {
    return Button(std::move(text));
}

} // namespace lvgl_modern::widgets
