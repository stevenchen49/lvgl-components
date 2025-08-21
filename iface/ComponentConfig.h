#pragma once

#include "lvgl.h"
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
        lv_flex_flow_t flexFlow = LV_FLEX_FLOW_ROW;      ///< 弹性布局方向
        lv_flex_align_t mainPlace = LV_FLEX_ALIGN_START; ///< 主轴对齐方式
        lv_flex_align_t crossPlace = LV_FLEX_ALIGN_START;///< 交叉轴对齐方式
        lv_flex_align_t trackPlace = LV_FLEX_ALIGN_START;///< 轨道对齐方式
        uint8_t rowGap = 0;                              ///< 行间距
        uint8_t columnGap = 0;                           ///< 列间距
        
        Layout() = default;
        Layout(lv_flex_flow_t flow) : flexFlow(flow) {}
    };

    /**
     * @brief 样式配置
     */
    struct Style {
        uint32_t bgColor = ColorConfig::Background;      ///< 背景色
        uint32_t textColor = ColorConfig::TextPrimary;   ///< 文本色
        uint32_t borderColor = ColorConfig::BorderPrimary;///< 边框色
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
        std::string content;                             ///< 文本内容
        const lv_font_t* font = nullptr;                 ///< 字体
        lv_text_align_t align = LV_TEXT_ALIGN_LEFT;      ///< 文本对齐
        uint8_t lineHeight = 0;                          ///< 行高
        bool autoSize = true;                            ///< 自动调整大小
        bool enabled = false;                            ///< 是否启用文本功能
        
        Text() = default;
        Text(const std::string& text) : content(text), enabled(true) {}
        Text(const std::string& text, const lv_font_t* f) : content(text), font(f), enabled(true) {}
    };

    /**
     * @brief 事件配置
     */
    struct Event {
        std::function<void(lv_event_t*)> onClick;        ///< 点击事件
        std::function<void(lv_event_t*)> onLongPress;    ///< 长按事件
        std::function<void(lv_event_t*)> onFocus;        ///< 焦点事件
        std::function<void(lv_event_t*)> onBlur;         ///< 失焦事件
        std::function<void(lv_event_t*)> onValueChange;  ///< 值变化事件
        
        Event() = default;
    };

    /**
     * @brief 动画配置
     */
    struct Animation {
        uint32_t duration = 300;                         ///< 动画持续时间(ms)
        lv_anim_path_cb_t path = lv_anim_path_ease_out;  ///< 动画路径
        bool enabled = true;                             ///< 是否启用动画
        
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
    ComponentConfig& setOnClick(std::function<void(lv_event_t*)> callback) {
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