#pragma once

#include "ColorConfig.h"
#include <string>

namespace Gui {

struct CheckboxConfig
{
    struct Color {
        uint32_t bgColor = ColorConfig::Transparent;      ///< 背景色
        uint32_t borderColor = ColorConfig::Grey400;      ///< 边框色
        uint32_t checkColor = ColorConfig::White;         ///< 勾选标记色
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
    
    CheckboxConfig() = default;
    
    CheckboxConfig(bool checked) : isChecked(checked) {}
    
    // ==================== 便捷方法 ====================
    
    /**
     * @brief 设置选中状态
     */
    CheckboxConfig& setChecked(bool checked) {
        isChecked = checked;
        return *this;
    }
    
    /**
     * @brief 设置可点击性
     */
    CheckboxConfig& setClickable(bool isClickable) {
        clickable = isClickable;
        return *this;
    }
    
    /**
     * @brief 设置可获得焦点性
     */
    CheckboxConfig& setFocusable(bool isFocusable) {
        focusable = isFocusable;
        return *this;
    }
    
    /**
     * @brief 设置可见性
     */
    CheckboxConfig& setVisible(bool isVisible) {
        visible = isVisible;
        return *this;
    }
    
    /**
     * @brief 设置启用状态
     */
    CheckboxConfig& setEnabled(bool isEnabled) {
        enabled = isEnabled;
        return *this;
    }

    // ==================== 静态方法 ====================
    
    /**
     * @brief 创建默认配置
     */
    static CheckboxConfig defaultConfig() {
        CheckboxConfig config;
        
        // Normal state: 透明背景，浅灰色边框
        config.normal.bgColor = ColorConfig::Transparent;
        config.normal.borderColor = ColorConfig::Grey400;
        config.normal.checkColor = ColorConfig::White;
        
        // Checked state: 亮绿色背景，白色勾选标记
        config.checked.bgColor = ColorConfig::Brand;
        config.checked.borderColor = ColorConfig::Transparent;
        config.checked.checkColor = ColorConfig::Black;
        
        // Disabled state: 中灰色背景，浅灰色勾选标记
        config.disabled.bgColor = ColorConfig::Grey300;
        config.disabled.borderColor = ColorConfig::Transparent;
        config.disabled.checkColor = ColorConfig::Grey500;
        
        config.isChecked = false;
        config.clickable = true;
        config.focusable = true;
        config.visible = true;
        config.enabled = true;
        
        return config;
    }
};

} // namespace Gui
