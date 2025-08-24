#pragma once

#include "ColorConfig.h"
#include <functional>
#include <string>

namespace Gui {

/**
 * @brief 组件配置结构体
 * 
 * 提供完整的组件配置选项，包括位置、尺寸、样式、事件等
 */
struct ComponentConfig
{
    /**
     * @brief 弹性布局方向
     */
    enum class FlexFlow {
        Row,            ///< 水平排列
        Column,         ///< 垂直排列
        RowReverse,     ///< 水平反向排列
        ColumnReverse   ///< 垂直反向排列
    };

    /**
     * @brief 弹性对齐方式
     */
    enum class FlexAlign {
        Start,          ///< 起始对齐
        End,            ///< 结束对齐
        Center,         ///< 居中对齐
        SpaceBetween,   ///< 两端对齐
        SpaceAround,    ///< 环绕对齐
        SpaceEvenly     ///< 均匀对齐
    };

    /**
     * @brief 文本对齐方式
     */
    enum class TextAlign {
        Left,           ///< 左对齐
        Center,         ///< 居中对齐
        Right,          ///< 右对齐
        Auto            ///< 自动对齐
    };

    /**
     * @brief 动画路径类型
     */
    enum class AnimPath {
        Linear,         ///< 线性
        EaseIn,         ///< 缓入
        EaseOut,        ///< 缓出
        EaseInOut,      ///< 缓入缓出
        Overshoot,      ///< 过冲
        Bounce          ///< 弹跳
    };
    /**
     * @brief 位置配置
     */
    struct Pos {
        int32_t x = 0;           ///< X 坐标
        int32_t y = 0;           ///< Y 坐标
        int32_t width = 0;       ///< 宽度 (0表示自动)
        int32_t height = 0;      ///< 高度 (0表示自动)
        
        Pos() = default;
        Pos(int32_t x, int32_t y) : x(x), y(y) {}
        Pos(int32_t x, int32_t y, int32_t w, int32_t h) : x(x), y(y), width(w), height(h) {}
    };

    /**
     * @brief 布局配置
     */
    struct Layout {
        FlexFlow flexFlow = FlexFlow::Row;          ///< 弹性布局方向
        FlexAlign mainPlace = FlexAlign::Start;     ///< 主轴对齐方式
        FlexAlign crossPlace = FlexAlign::Start;    ///< 交叉轴对齐方式
        FlexAlign trackPlace = FlexAlign::Start;    ///< 轨道对齐方式
        uint8_t rowGap = 0;                         ///< 行间距
        uint8_t columnGap = 0;                      ///< 列间距
        
        Layout() = default;
        Layout(FlexFlow flow) : flexFlow(flow) {}
    };

    /**
     * @brief 样式配置
     */
    struct Style {
        uint32_t bgColor = ColorConfig::BgBase;      ///< 背景色
        uint32_t textColor = ColorConfig::White;     ///< 文本色
        uint32_t borderColor = ColorConfig::Grey400; ///< 边框色
        uint8_t bgOpacity = 255;                         ///< 背景透明度
        uint8_t textOpacity = 255;                       ///< 文本透明度
        uint8_t borderOpacity = 255;                     ///< 边框透明度
        uint8_t borderWidth = 0;                         ///< 边框宽度
        uint8_t radius = 0;                              ///< 圆角半径
        uint8_t padding = 0;                             ///< 内边距
        uint8_t margin = 0;                              ///< 外边距
        
        Style() = default;
        Style(uint32_t bg, uint32_t text) : bgColor(bg), textColor(text) {}
    };

    /**
     * @brief 文本配置
     */
    struct Text {
        std::string content;                        ///< 文本内容
        void* font = nullptr;                       ///< 字体指针（隔离LVGL类型）
        TextAlign align = TextAlign::Left;          ///< 文本对齐
        uint8_t lineHeight = 0;                     ///< 行高
        bool autoSize = true;                       ///< 自动调整大小
        bool enabled = false;                       ///< 是否启用文本功能
        
        Text() = default;
        Text(const std::string& text) : content(text), enabled(true) {}
        Text(const std::string& text, void* f) : content(text), font(f), enabled(true) {}
    };

    /**
     * @brief 事件配置
     */
    struct Event {
        std::function<void(void*)> onClick;        ///< 点击事件（参数为事件指针）
        std::function<void(void*)> onLongPress;    ///< 长按事件
        std::function<void(void*)> onFocus;        ///< 焦点事件
        std::function<void(void*)> onBlur;         ///< 失焦事件
        std::function<void(void*)> onValueChange;  ///< 值变化事件
        
        Event() = default;
    };

    /**
     * @brief 动画配置
     */
    struct Animation {
        uint32_t duration = 300;                ///< 动画持续时间(ms)
        AnimPath path = AnimPath::EaseOut;      ///< 动画路径
        bool enabled = true;                    ///< 是否启用动画
        
        Animation() = default;
        Animation(uint32_t dur) : duration(dur) {}
    };

    // ==================== 成员变量 ====================
    
    Pos pos;                    ///< 位置配置
    Layout layout;              ///< 布局配置
    Style style;                ///< 样式配置
    Text text;                  ///< 文本配置
    Event event;                ///< 事件配置
    Animation animation;        ///< 动画配置
    
    bool visible = true;        ///< 是否可见
    bool enabled = true;        ///< 是否启用
    bool clickable = false;     ///< 是否可点击
    bool focusable = false;     ///< 是否可获得焦点
    
    std::string id;             ///< 组件ID
    void* userData = nullptr;   ///< 用户数据

    // ==================== 构造函数 ====================
    
    ComponentConfig() = default;
    
    ComponentConfig(const Pos& p) : pos(p) {}
    ComponentConfig(const Style& s) : style(s) {}
    ComponentConfig(const Text& t) : text(t) {}
    
    ComponentConfig(const Pos& p, const Style& s) : pos(p), style(s) {}
    ComponentConfig(const Pos& p, const Text& t) : pos(p), text(t) {}
    ComponentConfig(const Style& s, const Text& t) : style(s), text(t) {}
    
    ComponentConfig(const Pos& p, const Style& s, const Text& t) 
        : pos(p), style(s), text(t) {}

    // ==================== 便捷方法 ====================
    
    /**
     * @brief 设置位置
     */
    ComponentConfig& setPos(int32_t x, int32_t y) {
        pos.x = x; pos.y = y;
        return *this;
    }
    
    /**
     * @brief 设置尺寸
     */
    ComponentConfig& setSize(int32_t width, int32_t height) {
        pos.width = width; pos.height = height;
        return *this;
    }
    
    /**
     * @brief 设置背景色
     */
    ComponentConfig& setBgColor(uint32_t color) {
        style.bgColor = color;
        return *this;
    }
    
    /**
     * @brief 设置文本色
     */
    ComponentConfig& setTextColor(uint32_t color) {
        style.textColor = color;
        return *this;
    }
    
    /**
     * @brief 设置文本内容
     */
    ComponentConfig& setText(const std::string& content) {
        text.content = content;
        return *this;
    }
    
    /**
     * @brief 设置点击事件
     */
    template<typename Callback>
    ComponentConfig& setOnClick(Callback callback) {
        event.onClick = callback;
        return *this;
    }
    
    /**
     * @brief 设置组件ID
     */
    ComponentConfig& setId(const std::string& componentId) {
        id = componentId;
        return *this;
    }
    
    /**
     * @brief 设置用户数据
     */
    ComponentConfig& setUserData(void* data) {
        userData = data;
        return *this;
    }
};

} // namespace Gui