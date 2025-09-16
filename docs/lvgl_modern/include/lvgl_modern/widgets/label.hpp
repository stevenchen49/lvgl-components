#pragma once
// Label控件 - 借鉴wxUI的声明式设计

#include "../core/widget_base.hpp"
#include "../reactive/observable.hpp"
#include <mock_lvgl/lvgl.h>
#include <string>

namespace lvgl_modern::widgets {

class Label : public core::WidgetBase<Label> {
public:
    using Proxy = core::WidgetProxy<Label>;
    
    // 构造函数
    Label() = default;
    explicit Label(std::string text) : text_(std::move(text)) {}
    
    // 延迟构造实现
    lv_obj_t* createImpl(lv_obj_t* parent) override {
        auto* label = lv_label_create(parent);
        if (!text_.empty()) {
            lv_label_set_text(label, text_.c_str());
        }
        return label;
    }
    
    // 文本设置 - 方法链支持
    auto& text(std::string new_text) {
        text_ = std::move(new_text);
        if (native()) {
            threading::ThreadSafe::execute([this]() {
                lv_label_set_text(native(), text_.c_str());
            });
        }
        return self();
    }
    
    // 获取文本
    const std::string& getText() const { return text_; }
    
    // 字体大小设置
    auto& fontSize(int size) {
        font_size_ = size;
        // 在实际LVGL中会设置字体
        std::cout << "[Label] Font size set to: " << size << std::endl;
        return self();
    }
    
    // 颜色设置
    auto& color(lv_color_t color) {
        color_ = color;
        // 在实际LVGL中会设置颜色
        std::cout << "[Label] Color set to: 0x" << std::hex << color << std::dec << std::endl;
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
    
    // 代理绑定
    auto& withProxy(Proxy& proxy) {
        proxy.bind(this);
        return self();
    }
    
    // 静态工厂方法
    static std::unique_ptr<Label> create(std::string text = "") {
        return std::make_unique<Label>(std::move(text));
    }
    
protected:
    void applyStyle() override {
        core::WidgetBase<Label>::applyStyle();
        
        if (native()) {
            // 应用字体大小和颜色等样式
            if (font_size_ > 0) {
                std::cout << "[Label] Applying font size: " << font_size_ << std::endl;
            }
            if (color_ != 0) {
                std::cout << "[Label] Applying color: 0x" << std::hex << color_ << std::dec << std::endl;
            }
        }
    }
    
private:
    std::string text_;
    int font_size_ = 0;
    lv_color_t color_ = 0;
};

// 便利的工厂函数
inline auto createLabel(std::string text = "") {
    return Label(std::move(text));
}

} // namespace lvgl_modern::widgets
