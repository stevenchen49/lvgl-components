#pragma once

#include "ColorConfig.h"
#include <string>

namespace Gui {

struct RadioConfig
{
    struct Color {
        uint32_t bgColor = ColorConfig::Transparent;      ///< 背景色
        uint32_t borderColor = ColorConfig::Grey400;      ///< 边框色
        uint32_t dotColor = ColorConfig::White;           ///< 圆点色
    };

    Color normal;                    ///< 正常状态颜色
    Color checked;                   ///< 选中状态颜色
    Color disabled;                  ///< 禁用状态颜色

    bool isChecked = false;         ///< 是否被选中
    bool clickable = true;          ///< 是否可点击
    bool focusable = true;          ///< 是否可获得焦点
    bool visible = true;            ///< 是否可见
    bool enabled = true;            ///< 是否启用
    
    // ==================== 构造函数 ====================
    
    RadioConfig() = default;
    
    RadioConfig(bool checked) : isChecked(checked) {}
    
    // ==================== 便捷方法 ====================
    
    /**
     * @brief 设置选中状态
     */
    RadioConfig& setChecked(bool checked) {
        isChecked = checked;
        return *this;
    }
    
    /**
     * @brief 设置可点击性
     */
    RadioConfig& setClickable(bool clickable) {
        this->clickable = clickable;
        return *this;
    }
    
    /**
     * @brief 设置可获得焦点性
     */
    RadioConfig& setFocusable(bool focusable) {
        this->focusable = focusable;
        return *this;
    }
    
    /**
     * @brief 设置可见性
     */
    RadioConfig& setVisible(bool visible) {
        this->visible = visible;
        return *this;
    }
    
    /**
     * @brief 设置启用状态
     */
    RadioConfig& setEnabled(bool enabled) {
        this->enabled = enabled;
        return *this;
    }

    // ==================== 静态方法 ====================
    
    /**
     * @brief 创建默认配置
     */
    static RadioConfig defaultConfig() {
        RadioConfig config;
        
        // Normal state: 透明背景，浅灰色边框
        config.normal.bgColor = ColorConfig::Transparent;
        config.normal.borderColor = ColorConfig::Grey400;
        config.normal.dotColor = ColorConfig::White;
        
        // Checked state: 亮绿色背景，黑色圆点
        config.checked.bgColor = ColorConfig::Brand;
        config.checked.borderColor = ColorConfig::Transparent;
        config.checked.dotColor = ColorConfig::Black;
        
        // Disabled state: 中灰色背景，浅灰色圆点
        config.disabled.bgColor = ColorConfig::Grey300;
        config.disabled.borderColor = ColorConfig::Transparent;
        config.disabled.dotColor = ColorConfig::Grey500;
        
        config.isChecked = false;
        config.clickable = true;
        config.focusable = true;
        config.visible = true;
        config.enabled = true;
        
        return config;
    }
};

} // namespace Gui
