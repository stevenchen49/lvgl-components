#pragma once
// Slider控件 - 支持数值绑定和响应式编程

#include "../core/widget_base.hpp"
#include "../reactive/observable.hpp"
#include <mock_lvgl/lvgl.h>
#include <functional>
#include <algorithm>

namespace lvgl_modern::widgets {

class Slider : public core::WidgetBase<Slider> {
public:
    using Proxy = core::WidgetProxy<Slider>;
    using ValueChangedHandler = std::function<void(int)>;
    
    // 构造函数
    Slider() = default;
    Slider(int min, int max, int value = 0) 
        : min_(min), max_(max), value_(std::clamp(value, min, max)) {}
    
    // 延迟构造实现
    lv_obj_t* createImpl(lv_obj_t* parent) override {
        auto* slider = lv_slider_create(parent);
        lv_slider_set_range(slider, min_, max_);
        lv_slider_set_value(slider, value_, false);
        return slider;
    }
    
    // 数值设置
    auto& value(int new_value) {
        int clamped_value = std::clamp(new_value, min_, max_);
        if (value_ != clamped_value) {
            value_ = clamped_value;
            
            if (native()) {
                threading::ThreadSafe::execute([this]() {
                    lv_slider_set_value(native(), value_, false);
                });
            }
            
            // 触发值变化事件
            if (value_changed_handler_) {
                value_changed_handler_(value_);
            }
            
            // 更新响应式属性
            if (value_observable_) {
                value_observable_->set(value_);
            }
        }
        return self();
    }
    
    // 范围设置
    auto& range(int min, int max) {
        min_ = min;
        max_ = max;
        value_ = std::clamp(value_, min_, max_);
        
        if (native()) {
            threading::ThreadSafe::execute([this]() {
                lv_slider_set_range(native(), min_, max_);
                lv_slider_set_value(native(), value_, false);
            });
        }
        return self();
    }
    
    // 值变化事件绑定
    auto& onValueChanged(ValueChangedHandler handler) {
        value_changed_handler_ = std::move(handler);
        if (native()) {
            bindValueChangedEvent();
        }
        return self();
    }
    
    // 响应式数值绑定
    template<typename ObservableType>
    auto& bindValue(const ObservableType& observable) {
        observable.subscribe([this](const auto& val) {
            if constexpr (std::is_arithmetic_v<std::decay_t<decltype(val)>>) {
                value(static_cast<int>(val));
            }
        });
        return self();
    }
    
    // 创建响应式属性
    auto& asObservable() {
        if (!value_observable_) {
            value_observable_ = std::make_unique<reactive::ObservableProperty<int>>(value_);
        }
        return *value_observable_;
    }
    
    // 动画设置
    auto& animated(bool enable) {
        animated_ = enable;
        return self();
    }
    
    // 步长设置
    auto& step(int step_size) {
        step_ = step_size;
        return self();
    }
    
    // 模拟值变化（用于测试）
    void simulateValueChange(int new_value) {
        std::cout << "[Slider] Simulating value change to: " << new_value << std::endl;
        value(new_value);
        
        // 模拟LVGL事件
        if (value_changed_handler_) {
            threading::ThreadSafe::execute([this]() {
                value_changed_handler_(value_);
            });
        }
    }
    
    // 代理绑定
    auto& withProxy(Proxy& proxy) {
        proxy.bind(this);
        return self();
    }
    
    // 静态工厂方法
    static std::unique_ptr<Slider> create(int min = 0, int max = 100, int value = 0) {
        return std::make_unique<Slider>(min, max, value);
    }
    
    // 获取属性
    int getValue() const { return value_; }
    int getMin() const { return min_; }
    int getMax() const { return max_; }
    int getStep() const { return step_; }
    bool isAnimated() const { return animated_; }
    
protected:
    void bindEvents() override {
        if (value_changed_handler_) {
            bindValueChangedEvent();
        }
    }
    
private:
    void bindValueChangedEvent() {
        if (native() && value_changed_handler_) {
            // 在实际LVGL中绑定值变化事件
            lv_obj_add_event_cb(native(), 
                [](lv_event_t* e) {
                    auto* slider = static_cast<Slider*>(e->user_data);
                    if (slider && slider->value_changed_handler_) {
                        int new_value = lv_slider_get_value(slider->native());
                        slider->value_ = new_value;
                        slider->value_changed_handler_(new_value);
                        
                        // 更新响应式属性
                        if (slider->value_observable_) {
                            slider->value_observable_->set(new_value);
                        }
                    }
                }, 
                LV_EVENT_VALUE_CHANGED, this);
        }
    }
    
    int min_ = 0;
    int max_ = 100;
    int value_ = 0;
    int step_ = 1;
    bool animated_ = false;
    ValueChangedHandler value_changed_handler_;
    std::unique_ptr<reactive::ObservableProperty<int>> value_observable_;
};

// 便利的工厂函数
inline auto createSlider(int min = 0, int max = 100, int value = 0) {
    return Slider(min, max, value);
}

} // namespace lvgl_modern::widgets
