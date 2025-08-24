#pragma once

#include "ColorConfig.h"
#include <cstdint>

namespace Gui {

/**
 * @brief 开关组件配置
 * 
 * 支持开关的开启/关闭状态配置，包括轨道颜色、滑块颜色、图标颜色等
 */
struct SwitchConfig {
    /**
     * @brief 颜色配置结构
     */
    struct Color {
        uint32_t trackColor = ColorConfig::Grey400;      ///< 轨道颜色
        uint32_t knobColor = ColorConfig::White;         ///< 滑块颜色
        uint32_t iconColor = ColorConfig::White;         ///< 图标颜色
    };
    
    Color on;           ///< 开启状态颜色
    Color off;          ///< 关闭状态颜色
    Color disabled;     ///< 禁用状态颜色
    
    bool isOn = false;          ///< 是否开启
    bool clickable = true;      ///< 是否可点击
    bool focusable = true;      ///< 是否可获得焦点
    bool visible = true;        ///< 是否可见
    bool enabled = true;        ///< 是否启用
    
    /**
     * @brief 默认构造函数
     */
    SwitchConfig() = default;
    
    /**
     * @brief 带状态构造函数
     * @param on 是否开启
     */
    SwitchConfig(bool on) : isOn(on) {}
    
    // ==================== 便捷设置方法 ====================
    
    /**
     * @brief 设置开启状态
     * @param on 是否开启
     * @return 自身引用，支持链式调用
     */
    SwitchConfig& setOn(bool on) { isOn = on; return *this; }
    
    /**
     * @brief 设置可点击状态
     * @param clickable 是否可点击
     * @return 自身引用，支持链式调用
     */
    SwitchConfig& setClickable(bool clickable) { this->clickable = clickable; return *this; }
    
    /**
     * @brief 设置可获得焦点状态
     * @param focusable 是否可获得焦点
     * @return 自身引用，支持链式调用
     */
    SwitchConfig& setFocusable(bool focusable) { this->focusable = focusable; return *this; }
    
    /**
     * @brief 设置可见状态
     * @param visible 是否可见
     * @return 自身引用，支持链式调用
     */
    SwitchConfig& setVisible(bool visible) { this->visible = visible; return *this; }
    
    /**
     * @brief 设置启用状态
     * @param enabled 是否启用
     * @return 自身引用，支持链式调用
     */
    SwitchConfig& setEnabled(bool enabled) { this->enabled = enabled; return *this; }
    
    // ==================== 静态预设方法 ====================
    
    /**
     * @brief 默认配置预设
     * 
     * 开启状态：亮绿色轨道，黑色滑块，亮绿色图标
     * 关闭状态：深灰色轨道，浅灰色滑块，无图标
     * 
     * @return 默认配置
     */
    static SwitchConfig defaultConfig() {
        SwitchConfig config;
        
        // 开启状态 - 亮绿色主题
        config.on.trackColor = ColorConfig::Brand;      // 亮绿色轨道
        config.on.knobColor = ColorConfig::Black;       // 黑色滑块
        config.on.iconColor = ColorConfig::Brand;       // 亮绿色图标
        
        // 关闭状态 - 深灰色主题
        config.off.trackColor = ColorConfig::Grey400;   // 深灰色轨道
        config.off.knobColor = ColorConfig::Grey300;    // 浅灰色滑块
        config.off.iconColor = ColorConfig::Transparent; // 无图标
        
        // 禁用状态 - 更深的灰色
        config.disabled.trackColor = ColorConfig::Grey500;
        config.disabled.knobColor = ColorConfig::Grey400;
        config.disabled.iconColor = ColorConfig::Transparent;
        
        // 默认状态
        config.isOn = false;
        config.clickable = true;
        config.focusable = true;
        config.visible = true;
        config.enabled = true;
        
        return config;
    }
    
    /**
     * @brief 橄榄绿主题预设
     * 
     * 开启状态：橄榄绿色轨道，黑色滑块，橄榄绿色图标
     * 关闭状态：深灰色轨道，深灰色滑块，无图标
     * 
     * @return 橄榄绿主题配置
     */
    static SwitchConfig oliveConfig() {
        SwitchConfig config;
        
        // 开启状态 - 橄榄绿色主题
        config.on.trackColor = 0x556B2F;               // 橄榄绿色轨道
        config.on.knobColor = ColorConfig::Black;      // 黑色滑块
        config.on.iconColor = 0x556B2F;                // 橄榄绿色图标
        
        // 关闭状态 - 深灰色主题
        config.off.trackColor = ColorConfig::Grey400;  // 深灰色轨道
        config.off.knobColor = ColorConfig::Grey500;   // 深灰色滑块
        config.off.iconColor = ColorConfig::Transparent; // 无图标
        
        // 禁用状态
        config.disabled.trackColor = ColorConfig::Grey500;
        config.disabled.knobColor = ColorConfig::Grey400;
        config.disabled.iconColor = ColorConfig::Transparent;
        
        // 默认状态
        config.isOn = false;
        config.clickable = true;
        config.focusable = true;
        config.visible = true;
        config.enabled = true;
        
        return config;
    }
};

} // namespace Gui
