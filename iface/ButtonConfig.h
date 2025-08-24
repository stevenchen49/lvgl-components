#pragma once

#include "ColorConfig.h"
#include <string>

namespace Gui {

/**
 * @brief 按钮配置结构体
 * 
 * 继承自 ComponentConfig，添加按钮特有的配置选项
 */
struct ButtonConfig
{
    /**
     * @brief 按钮状态配置
     */
    struct State {
        uint32_t normalBgColor = ColorConfig::Primary;      ///< 正常状态背景色
        uint32_t pressedBgColor = ColorConfig::Grey300;     ///< 按下状态背景色
        uint32_t disabledBgColor = ColorConfig::Grey400;    ///< 禁用状态背景色
        uint32_t normalTextColor = ColorConfig::White;      ///< 正常状态文本色
        uint32_t pressedTextColor = ColorConfig::White;     ///< 按下状态文本色
        uint32_t disabledTextColor = ColorConfig::Grey500;  ///< 禁用状态文本色
        
        State() = default;
        State(uint32_t bg, uint32_t text) : normalBgColor(bg), normalTextColor(text) {}
    };

    /**
     * @brief 按钮样式配置
     */
    struct ButtonStyle {
        uint8_t cornerRadius = 8;                           ///< 圆角半径
        uint8_t borderWidth = 0;                            ///< 边框宽度
        uint32_t borderColor = ColorConfig::Grey400;        ///< 边框颜色
        uint8_t shadowWidth = 2;                            ///< 阴影宽度
        uint32_t shadowColor = ColorConfig::Grey200;        ///< 阴影颜色
        uint8_t shadowOffsetX = 0;                          ///< 阴影X偏移
        uint8_t shadowOffsetY = 2;                          ///< 阴影Y偏移
        
        ButtonStyle() = default;
    };

    // ==================== 成员变量 ====================
    
    State state;                    ///< 按钮状态配置
    ButtonStyle buttonStyle;        ///< 按钮样式配置
    std::string buttonText;         ///< 按钮文本
    bool toggleMode = false;        ///< 是否为切换模式
    bool checked = false;           ///< 是否被选中（切换模式）
    bool clickable = true;          ///< 是否可点击
    bool focusable = true;          ///< 是否可获得焦点
    bool visible = true;            ///< 是否可见
    bool enabled = true;            ///< 是否启用
    
    // ==================== 构造函数 ====================
    
    ButtonConfig() = default;
    
    ButtonConfig(const std::string& text) : buttonText(text) {}
    
    ButtonConfig(const std::string& text, const State& s) 
        : buttonText(text), state(s) {}
    
    ButtonConfig(const std::string& text, const State& s, const ButtonStyle& bs) 
        : buttonText(text), state(s), buttonStyle(bs) {}

    // ==================== 便捷方法 ====================
    
    /**
     * @brief 设置按钮文本
     */
    ButtonConfig& setButtonText(const std::string& text) {
        buttonText = text;
        return *this;
    }
    
    /**
     * @brief 设置正常状态颜色
     */
    ButtonConfig& setNormalColors(uint32_t bgColor, uint32_t textColor) {
        state.normalBgColor = bgColor;
        state.normalTextColor = textColor;
        return *this;
    }
    
    /**
     * @brief 设置按下状态颜色
     */
    ButtonConfig& setPressedColors(uint32_t bgColor, uint32_t textColor) {
        state.pressedBgColor = bgColor;
        state.pressedTextColor = textColor;
        return *this;
    }
    
    /**
     * @brief 设置禁用状态颜色
     */
    ButtonConfig& setDisabledColors(uint32_t bgColor, uint32_t textColor) {
        state.disabledBgColor = bgColor;
        state.disabledTextColor = textColor;
        return *this;
    }
    
    /**
     * @brief 设置圆角半径
     */
    ButtonConfig& setCornerRadius(uint8_t radius) {
        buttonStyle.cornerRadius = radius;
        return *this;
    }
    
    /**
     * @brief 设置边框
     */
    ButtonConfig& setBorder(uint8_t width, uint32_t color) {
        buttonStyle.borderWidth = width;
        buttonStyle.borderColor = color;
        return *this;
    }
    
    /**
     * @brief 设置阴影
     */
    ButtonConfig& setShadow(uint8_t width, uint32_t color, uint8_t offsetX = 0, uint8_t offsetY = 2) {
        buttonStyle.shadowWidth = width;
        buttonStyle.shadowColor = color;
        buttonStyle.shadowOffsetX = offsetX;
        buttonStyle.shadowOffsetY = offsetY;
        return *this;
    }
    
    /**
     * @brief 设置切换模式
     */
    ButtonConfig& setToggleMode(bool enable) {
        toggleMode = enable;
        return *this;
    }
    
    /**
     * @brief 设置选中状态
     */
    ButtonConfig& setChecked(bool isChecked) {
        checked = isChecked;
        return *this;
    }
    
    /**
     * @brief 设置可点击性
     */
    ButtonConfig& setClickable(bool isClickable) {
        clickable = isClickable;
        return *this;
    }
    
    /**
     * @brief 设置可获得焦点性
     */
    ButtonConfig& setFocusable(bool isFocusable) {
        focusable = isFocusable;
        return *this;
    }
    
    /**
     * @brief 设置可见性
     */
    ButtonConfig& setVisible(bool isVisible) {
        visible = isVisible;
        return *this;
    }
    
    /**
     * @brief 设置启用状态
     */
    ButtonConfig& setEnabled(bool isEnabled) {
        enabled = isEnabled;
        return *this;
    }

    // ==================== 静态方法 ====================
    
    /**
     * @brief 创建默认配置
     */
    static ButtonConfig defaultConfig() {
        ButtonConfig config;
        config.setNormalColors(ColorConfig::Primary, ColorConfig::White);
        config.setPressedColors(ColorConfig::Grey300, ColorConfig::White);
        config.setDisabledColors(ColorConfig::Grey400, ColorConfig::Grey500);
        config.setCornerRadius(8);
        config.setShadow(2, ColorConfig::Grey200);
        config.clickable = true;
        config.focusable = true;
        config.visible = true;
        config.enabled = true;
        return config;
    }
    
    /**
     * @brief 创建主要按钮配置
     */
    static ButtonConfig primaryConfig(const std::string& text = "") {
        ButtonConfig config(text);
        config.setNormalColors(ColorConfig::Primary, ColorConfig::White);
        config.setPressedColors(ColorConfig::Grey300, ColorConfig::White);
        config.setDisabledColors(ColorConfig::Grey400, ColorConfig::Grey500);
        config.setCornerRadius(8);
        config.setShadow(2, ColorConfig::Grey200);
        config.clickable = true;
        config.focusable = true;
        config.visible = true;
        config.enabled = true;
        return config;
    }
    
    /**
     * @brief 创建次要按钮配置
     */
    static ButtonConfig secondaryConfig(const std::string& text = "") {
        ButtonConfig config(text);
        config.setNormalColors(ColorConfig::Secondary, ColorConfig::White);
        config.setPressedColors(ColorConfig::Grey300, ColorConfig::White);
        config.setDisabledColors(ColorConfig::Grey400, ColorConfig::Grey500);
        config.setCornerRadius(8);
        config.setBorder(1, ColorConfig::Grey400);
        config.clickable = true;
        config.focusable = true;
        config.visible = true;
        config.enabled = true;
        return config;
    }
    
    /**
     * @brief 创建成功按钮配置
     */
    static ButtonConfig successConfig(const std::string& text = "") {
        ButtonConfig config(text);
        config.setNormalColors(ColorConfig::Info, ColorConfig::White);
        config.setPressedColors(ColorConfig::Grey700, ColorConfig::White);
        config.setDisabledColors(ColorConfig::Grey400, ColorConfig::Grey500);
        config.setCornerRadius(8);
        config.setShadow(2, ColorConfig::Grey200);
        config.clickable = true;
        config.focusable = true;
        config.visible = true;
        config.enabled = true;
        return config;
    }
    
    /**
     * @brief 创建危险按钮配置
     */
    static ButtonConfig dangerConfig(const std::string& text = "") {
        ButtonConfig config(text);
        config.setNormalColors(ColorConfig::Danger, ColorConfig::White);
        config.setPressedColors(ColorConfig::Grey700, ColorConfig::White);
        config.setDisabledColors(ColorConfig::Grey400, ColorConfig::Grey500);
        config.setCornerRadius(8);
        config.setShadow(2, ColorConfig::Grey200);
        config.clickable = true;
        config.focusable = true;
        config.visible = true;
        config.enabled = true;
        return config;
    }
};

} // namespace Gui