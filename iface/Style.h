#pragma once
#include <cstdint>
#include "ColorConfig.h"

namespace Gui {

struct Size {
    int width;
    int height;
    
    Size() : width(0), height(0) {}
    Size(int w, int h) : width(w), height(h) {}
};

struct Position {
    int x;
    int y;
    
    Position() : x(0), y(0) {}
    Position(int x_, int y_) : x(x_), y(y_) {}
};

// 组件部件类型 - 不依赖 LVGL
namespace Part {
    enum class Type {
        Main,           // 主要部分
        Scrollbar,      // 滚动条
        Indicator,      // 指示器
        Knob,           // 旋钮
        Selected,       // 选中项
        Items,          // 列表项
        Cursor,         // 光标
        Custom1,        // 自定义部件
        Custom2,
        Custom3,
        Custom4,
        Any             // 任意部件
    };
}

// 组件状态类型 - 不依赖 LVGL
namespace State {
    enum class Type {
        Normal,         // 正常状态
        Checked,        // 选中状态
        Focused,        // 焦点状态
        Pressed,        // 按下状态
        Disabled,       // 禁用状态
        Hovered,        // 悬停状态
        Edited,         // 编辑状态
        Any             // 任意状态
    };
}

// 直观的样式系统 - 完全独立于底层实现
namespace Style {
    
    // 字体相关
    namespace Font {
        enum class Size {
            XSmall,     // 10px
            Small,      // 12px
            Medium,     // 14px
            Large,      // 16px
            XLarge,     // 18px
            XXLarge     // 24px
        };
        
        enum class Weight {
            Thin,
            Light,
            Normal,
            Bold,
            Black
        };
        
        enum class Style {
            Normal,
            Italic
        };
    }
    
    // 文本相关
    namespace Text {
        enum class Align {
            Left,
            Center,
            Right,
            Justify
        };
        
        enum class Decoration {
            None,
            Underline,
            Strikethrough
        };
    }
    
    // 尺寸相关
    namespace Size {
        enum class Unit {
            Pixel,      // 像素
            Percent,    // 百分比
            Auto        // 自动
        };
    }
    
    // 间距相关
    namespace Spacing {
        // 内边距
        struct Padding {
            int top = 0;
            int right = 0;
            int bottom = 0;
            int left = 0;
            
            Padding() = default;
            Padding(int all) : top(all), right(all), bottom(all), left(all) {}
            Padding(int vertical, int horizontal) 
                : top(vertical), right(horizontal), bottom(vertical), left(horizontal) {}
            Padding(int t, int r, int b, int l) : top(t), right(r), bottom(b), left(l) {}
        };
        
        // 外边距
        struct Margin {
            int top = 0;
            int right = 0;
            int bottom = 0;
            int left = 0;
            
            Margin() = default;
            Margin(int all) : top(all), right(all), bottom(all), left(all) {}
            Margin(int vertical, int horizontal) 
                : top(vertical), right(horizontal), bottom(vertical), left(horizontal) {}
            Margin(int t, int r, int b, int l) : top(t), right(r), bottom(b), left(l) {}
        };
    }
    
    // 边框相关
    namespace Border {
        enum class Style {
            None,
            Solid,
            Dashed,
            Dotted
        };
        
        enum class Side {
            All,
            Top,
            Right,
            Bottom,
            Left
        };
        
        struct Config {
            int width = 0;
            uint32_t color = ColorConfig::Black;
            Style style = Style::Solid;
            Side side = Side::All;
        };
    }
    
    // 背景相关
    namespace Background {
        enum class Type {
            Color,
            Gradient,
            Image
        };
        
        enum class GradientDirection {
            TopToBottom,
            LeftToRight,
            DiagonalTL,
            DiagonalTR
        };
        
        struct Gradient {
            uint32_t startColor;
            uint32_t endColor;
            GradientDirection direction = GradientDirection::TopToBottom;
        };
    }
    
    // 阴影相关
    namespace Shadow {
        struct Config {
            int offsetX = 0;
            int offsetY = 0;
            int blur = 0;
            int spread = 0;
            uint32_t color = ColorConfig::Black;
            int opacity = 255; // 0-255
        };
    }
    
    // 形状相关
    namespace Shape {
        struct BorderRadius {
            int topLeft = 0;
            int topRight = 0;
            int bottomRight = 0;
            int bottomLeft = 0;
            
            BorderRadius() = default;
            BorderRadius(int all) : topLeft(all), topRight(all), bottomRight(all), bottomLeft(all) {}
            BorderRadius(int tl, int tr, int br, int bl) 
                : topLeft(tl), topRight(tr), bottomRight(br), bottomLeft(bl) {}
        };
    }
}

// 统一的样式属性结构
struct StyleProperty {
    enum class Type {
        // 尺寸
        Width,
        Height,
        MinWidth,
        MaxWidth,
        MinHeight,
        MaxHeight,
        
        // 文本
        TextColor,
        TextSize,
        TextAlign,
        TextDecoration,
        
        // 背景
        BackgroundColor,
        BackgroundOpacity,
        
        // 边框
        BorderWidth,
        BorderColor,
        BorderStyle,
        BorderRadius,
        
        // 间距
        Padding,
        Margin,
        
        // 阴影
        Shadow,
        
        // 透明度
        Opacity
    };
    
    Type type;
    
    // 联合体存储不同类型的值
    union Value {
        int intValue;
        uint32_t colorValue;
        Style::Font::Size fontSizeValue;
        Style::Text::Align textAlignValue;
        Style::Text::Decoration textDecorationValue;
        Style::Spacing::Padding paddingValue;
        Style::Spacing::Margin marginValue;
        Style::Border::Config borderValue;
        Style::Shape::BorderRadius radiusValue;
        Style::Shadow::Config shadowValue;
        
        Value() : intValue(0) {}
        Value(int v) : intValue(v) {}
        Value(uint32_t c) : colorValue(c) {}
        Value(Style::Font::Size fs) : fontSizeValue(fs) {}
        Value(Style::Text::Align ta) : textAlignValue(ta) {}
        Value(Style::Text::Decoration td) : textDecorationValue(td) {}
        Value(const Style::Spacing::Padding& p) : paddingValue(p) {}
        Value(const Style::Spacing::Margin& m) : marginValue(m) {}
        Value(const Style::Border::Config& b) : borderValue(b) {}
        Value(const Style::Shape::BorderRadius& r) : radiusValue(r) {}
        Value(const Style::Shadow::Config& s) : shadowValue(s) {}
    } value;
    
    Part::Type part = Part::Type::Main;
    State::Type state = State::Type::Normal;
    
    // 构造函数
    StyleProperty(Type t, Value v, Part::Type p = Part::Type::Main, State::Type s = State::Type::Normal)
        : type(t), value(v), part(p), state(s) {}
};

namespace Layout {
    enum class Horizontal {
        Leading,
        Center,
        Trailing
    };

    enum class Vertical {
        Top,
        Center,
        Bottom
    };

    enum class Direction {
        Row,
        Column
    };

    enum class Wrap {
        NoWrap,
        Wrap
    };

    enum class Justify {
        Start,
        Center,
        End,
        SpaceBetween,
        SpaceAround,
        SpaceEvenly
    };

    enum class Align {
        Start,
        Center,
        End,
        Stretch,
        Baseline
    };
}

} // namespace Gui