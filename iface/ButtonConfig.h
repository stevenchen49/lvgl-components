#pragma once

#include "ColorConfig.h"
#include <string>

namespace Gui {

struct ButtonConfig
{
    struct Color {
        uint32_t bgColor = ColorConfig::Primary;      ///< 背景色
        uint32_t textColor = ColorConfig::White;     ///< 文本色
        uint32_t borderColor = ColorConfig::Grey400; ///< 边框色
   };

    Color normal;                    ///< 正常状态颜色
    Color pressed;                   ///< 按下状态颜色
    Color disabled;                  ///< 禁用状态颜色

    bool toggleMode = false;        ///< 是否为切换模式
    bool checked = false;           ///< 是否被选中（切换模式）
    bool clickable = true;          ///< 是否可点击
    bool focusable = true;          ///< 是否可获得焦点
    bool visible = true;            ///< 是否可见
    bool enabled = true;            ///< 是否启用
     
    // prs is short fo preset
    static ButtonConfig prsPrimary()
    {
        ButtonConfig config;

        // Normal state: 亮绿色背景，黑色文本，无边框
        config.normal.bgColor = ColorConfig::Brand;  // 亮绿色背景
        config.normal.textColor = ColorConfig::Black;  // 黑色文本
        config.normal.borderColor = ColorConfig::Transparent;  // 无边框

        // Pressed state: 深灰色背景，白色文本，浅灰色边框
        config.pressed.bgColor = ColorConfig::Grey300;  // 深灰色背景
        config.pressed.textColor = ColorConfig::White;  // 白色文本
        config.pressed.borderColor = ColorConfig::Grey400;  // 浅灰色边框

        // Disabled state: 很深的灰色背景，浅灰色文本，无边框
        config.disabled.bgColor = ColorConfig::Grey200;  // 很深的灰色背景
        config.disabled.textColor = ColorConfig::Grey500;  // 浅灰色文本
        config.disabled.borderColor = ColorConfig::Transparent;  // 无边框

        config.toggleMode = false;
        config.checked = false;
        config.clickable = true;
        config.focusable = true;
        config.visible = true;
        config.enabled = true;

        return config;
    }
    
    // prs is short for preset
    static ButtonConfig prsText()
    {
        ButtonConfig config;

        // Normal state: 白色文本，透明背景
        config.normal.bgColor = ColorConfig::Transparent;  // 透明背景
        config.normal.textColor = ColorConfig::White;
        config.normal.borderColor = ColorConfig::Transparent;  // 透明边框

        // Pressed state: 白色文本，深灰色背景
        config.pressed.bgColor = ColorConfig::Grey700;  // 深灰色背景
        config.pressed.textColor = ColorConfig::White;
        config.pressed.borderColor = ColorConfig::Transparent;  // 透明边框

        // Disabled state: 浅灰色文本，透明背景
        config.disabled.bgColor = ColorConfig::Transparent;  // 透明背景
        config.disabled.textColor = ColorConfig::Grey500;  // 浅灰色文本
        config.disabled.borderColor = ColorConfig::Transparent;  // 透明边框

        config.toggleMode = false;
        config.checked = false;
        config.clickable = true;
        config.focusable = true;
        config.visible = true;
        config.enabled = true;

        return config;
    }    
};

} // namespace Gui