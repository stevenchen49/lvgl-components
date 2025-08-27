#pragma once

#include "Adaptor.h"
#include "Style.h"

#include <functional>
#include <vector>

namespace Gui {

template <typename Derived>
class Modifier 
{
public:
    using Func = std::function<void(lv_obj_t*)>;

    virtual ~Modifier() = default;

public:
    // 基础样式修饰符
    Derived& size(const Size& size) &
    {
        custom([size](lv_obj_t* obj) {
            _lvSetSize(obj, size);
        });
        return static_cast<Derived&>(*this);
    }
    Derived&& size(const Size& size) &&
    {
        return std::move(static_cast<Derived&>(*this).size(size));
    }

    Derived& width(int width) &
    {
        custom([width](lv_obj_t* obj) {
            _lvSetWidth(obj, width);
        });
        return static_cast<Derived&>(*this);
    }
    Derived&& width(int width) &&
    {
        return std::move(static_cast<Derived&>(*this).width(width));
    }

    Derived& height(int height) &
    {
        custom([height](lv_obj_t* obj) {
            _lvSetHeight(obj, height);
        });
        return static_cast<Derived&>(*this);
    }
    Derived&& height(int height) &&
    {
        return std::move(static_cast<Derived&>(*this).height(height));
    }

    Derived& bgColor(lv_color_t color) &
    {
        custom([color](lv_obj_t* obj) {
            _lvSetBgColor(obj, color);
        });
        return static_cast<Derived&>(*this);
    }
    Derived&& bgColor(lv_color_t color) &&
    {
        return std::move(static_cast<Derived&>(*this).bgColor(color));
    }

    // 重载版本接受十六进制颜色值
    Derived& bgColor(uint32_t hex_color) &
    {
        return bgColor(lv_color_hex(hex_color));
    }
    Derived&& bgColor(uint32_t hex_color) &&
    {
        return std::move(static_cast<Derived&>(*this).bgColor(hex_color));
    }

    // 新增：简化的样式修饰符
    Derived& style(const StyleProperty& prop) &
    {
        custom([prop](lv_obj_t* obj) {
            _lvSetStyle(obj, prop);
        });
        return static_cast<Derived&>(*this);
    }
    Derived&& style(const StyleProperty& prop) &&
    {
        return std::move(static_cast<Derived&>(*this).style(prop));
    }

    // 便捷的样式修饰符 - 使用新的简化系统
    Derived& textColor(uint32_t color, Part::Type part = Part::Type::Main) &
    {
        return style(StyleProperty(StyleProperty::Type::TextColor, color, part));
    }
    Derived&& textColor(uint32_t color, Part::Type part = Part::Type::Main) &&
    {
        return std::move(static_cast<Derived&>(*this).textColor(color, part));
    }

    Derived& fontSize(Style::Font::Size size, Part::Type part = Part::Type::Main) &
    {
        return style(StyleProperty(StyleProperty::Type::TextSize, size, part));
    }
    Derived&& fontSize(Style::Font::Size size, Part::Type part = Part::Type::Main) &&
    {
        return std::move(static_cast<Derived&>(*this).fontSize(size, part));
    }

    Derived& radius(int r, Part::Type part = Part::Type::Main) &
    {
        Style::Shape::BorderRadius radius(r);
        return style(StyleProperty(StyleProperty::Type::BorderRadius, radius, part));
    }
    Derived&& radius(int r, Part::Type part = Part::Type::Main) &&
    {
        return std::move(static_cast<Derived&>(*this).radius(r, part));
    }

    Derived& borderWidth(int w, Part::Type part = Part::Type::Main) &
    {
        return style(StyleProperty(StyleProperty::Type::BorderWidth, w, part));
    }
    Derived&& borderWidth(int w, Part::Type part = Part::Type::Main) &&
    {
        return std::move(static_cast<Derived&>(*this).borderWidth(w, part));
    }

    Derived& borderColor(uint32_t color, Part::Type part = Part::Type::Main) &
    {
        return style(StyleProperty(StyleProperty::Type::BorderColor, color, part));
    }
    Derived&& borderColor(uint32_t color, Part::Type part = Part::Type::Main) &&
    {
        return std::move(static_cast<Derived&>(*this).borderColor(color, part));
    }

    Derived& padding(int p, Part::Type part = Part::Type::Main) &
    {
        Style::Spacing::Padding padding(p);
        return style(StyleProperty(StyleProperty::Type::Padding, padding, part));
    }
    Derived&& padding(int p, Part::Type part = Part::Type::Main) &&
    {
        return std::move(static_cast<Derived&>(*this).padding(p, part));
    }

    Derived& margin(int m, Part::Type part = Part::Type::Main) &
    {
        Style::Spacing::Margin margin(m);
        return style(StyleProperty(StyleProperty::Type::Margin, margin, part));
    }
    Derived&& margin(int m, Part::Type part = Part::Type::Main) &&
    {
        return std::move(static_cast<Derived&>(*this).margin(m, part));
    }

    Derived& opacity(int o, Part::Type part = Part::Type::Main) &
    {
        return style(StyleProperty(StyleProperty::Type::Opacity, o, part));
    }
    Derived&& opacity(int o, Part::Type part = Part::Type::Main) &&
    {
        return std::move(static_cast<Derived&>(*this).opacity(o, part));
    }

    // 状态特定的样式修饰符
    Derived& pressedStyle(Func func) &
    {
        custom([func](lv_obj_t* obj) {
            _lvAddState(obj, LV_STATE_PRESSED);
            func(obj);
            _lvRemoveState(obj, LV_STATE_PRESSED);
        });
        return static_cast<Derived&>(*this);
    }
    Derived&& pressedStyle(Func func) &&
    {
        return std::move(static_cast<Derived&>(*this).pressedStyle(func));
    }

    Derived& focusedStyle(Func func) &
    {
        custom([func](lv_obj_t* obj) {
            _lvAddState(obj, LV_STATE_FOCUSED);
            func(obj);
            _lvRemoveState(obj, LV_STATE_FOCUSED);
        });
        return static_cast<Derived&>(*this);
    }
    Derived&& focusedStyle(Func func) &&
    {
        return std::move(static_cast<Derived&>(*this).focusedStyle(func));
    }

    Derived& disabledStyle(Func func) &
    {
        custom([func](lv_obj_t* obj) {
            _lvAddState(obj, LV_STATE_DISABLED);
            func(obj);
            _lvRemoveState(obj, LV_STATE_DISABLED);
        });
        return static_cast<Derived&>(*this);
    }
    Derived&& disabledStyle(Func func) &&
    {
        return std::move(static_cast<Derived&>(*this).disabledStyle(func));
    }

    // 阴影和轮廓
    Derived& shadow(int offsetX, int offsetY, int blur, int spread, uint32_t color, int opacity = 255) &
    {
        Style::Shadow::Config shadowConfig;
        shadowConfig.offsetX = offsetX;
        shadowConfig.offsetY = offsetY;
        shadowConfig.blur = blur;
        shadowConfig.spread = spread;
        shadowConfig.color = color;
        shadowConfig.opacity = opacity;
        
        return style(StyleProperty(StyleProperty::Type::Shadow, shadowConfig));
    }
    Derived&& shadow(int offsetX, int offsetY, int blur, int spread, uint32_t color, int opacity = 255) &&
    {
        return std::move(static_cast<Derived&>(*this).shadow(offsetX, offsetY, blur, spread, color, opacity));
    }

public:
    Derived& custom(Func func) &
    {
        mFuncs.push_back(std::move(func));
        return static_cast<Derived&>(*this);
    }
    Derived&& custom(Func func) &&
    {
        return std::move(static_cast<Derived&>(*this).custom(func));
    }

    Derived& condition(bool condition, Func func) &
    {
        if (condition) {
            mFuncs.push_back(std::move(func));
        }
        return static_cast<Derived&>(*this);
    }
    Derived&& condition(bool condition, Func func) &&
    {
        return std::move(static_cast<Derived&>(*this).condition(condition, func));
    }

protected:
    void _applyAllModifiers(lv_obj_t* obj)
    {
        for (auto& func : mFuncs) {
            func(obj);
        }
    }

private:
    std::vector<Func> mFuncs;
};

} // namespace Gui