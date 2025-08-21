#pragma once

#include "Component.h"
#include "ButtonConfig.h"

namespace Gui {

/**
 * @brief 按钮组件
 * 
 * 基于 LVGL lv_button 的按钮组件封装
 */
class Button : public Component
{
public:
    Button();
    Button(const ButtonConfig& config);
    Button(const std::string& text);
    Button(const std::string& text, const ButtonConfig& config);
    virtual ~Button();

    /**
     * @brief 创建按钮对象
     */
    lv_obj_t* createObject(lv_obj_t* parent) override;

    Button& genObjectSync(lv_obj_t* parent = nullptr) override 
    {
        Component::genObjectSync(parent);
        return *this;
    }

    /**
     * @brief 应用按钮配置
     */
    void applyButtonConfig();

    // ==================== 按钮特有方法 ====================
    
    /**
     * @brief 设置按钮配置
     */
    Button& setConfig(const ButtonConfig& config);

    /**
     * @brief 设置按钮文本
     */
    Button& setButtonText(const std::string& text);

    /**
     * @brief 设置按钮状态
     */
    Button& setButtonState(lv_state_t state);

    /**
     * @brief 设置切换模式
     */
    Button& setToggleMode(bool enable);

    /**
     * @brief 设置选中状态
     */
    Button& setChecked(bool checked);

    /**
     * @brief 获取按钮文本
     */
    std::string getButtonText() const;

    /**
     * @brief 获取按钮状态
     */
    lv_state_t getButtonState() const;

    /**
     * @brief 检查是否为切换模式
     */
    bool isToggleMode() const;

    /**
     * @brief 检查是否被选中
     */
    bool isChecked() const;

    // ==================== 便捷方法 ====================
    
    /**
     * @brief 显示按钮
     */
    Button& show();

    /**
     * @brief 隐藏按钮
     */
    Button& hide();

    /**
     * @brief 启用按钮
     */
    Button& enable();

    /**
     * @brief 禁用按钮
     */
    Button& disable();

    /**
     * @brief 设置点击事件
     */
    Button& setOnClick(std::function<void(lv_event_t*)> callback);

    /**
     * @brief 设置长按事件
     */
    Button& setOnLongPress(std::function<void(lv_event_t*)> callback);

    /**
     * @brief 设置值变化事件
     */
    Button& setOnValueChange(std::function<void(lv_event_t*)> callback);

    // ==================== 获取方法 ====================
    
    /**
     * @brief 获取按钮配置
     */
    const ButtonConfig& getButtonConfig() const { return mButtonConfig; }

protected:
    /**
     * @brief 应用按钮样式
     */
    void applyButtonStyle();

    /**
     * @brief 应用按钮状态样式
     */
    void applyButtonStateStyle();

    static lv_obj_t* _lvCreateButton(lv_obj_t* parent);
    static void _lvSetConfig(lv_obj_t* obj, const ButtonConfig& config);
    static void _lvSetButtonText(lv_obj_t* obj, const std::string& text);
    static void _lvSetButtonState(lv_obj_t* obj, lv_state_t state);
    static void _lvClearButtonState(lv_obj_t* obj, lv_state_t state);
    static void _lvAddButtonState(lv_obj_t* obj, lv_state_t state);
    static void _lvSetToggleMode(lv_obj_t* obj, bool enable);
    static void _lvSetChecked(lv_obj_t* obj, bool checked);
    static void _lvShowButton(lv_obj_t* obj);
    static void _lvHideButton(lv_obj_t* obj);
    static void _lvEnableButton(lv_obj_t* obj);
    static void _lvDisableButton(lv_obj_t* obj);
    static std::string _lvGetButtonText(lv_obj_t* obj);
    static lv_state_t _lvGetButtonState(lv_obj_t* obj);
    static bool _lvIsToggleMode(lv_obj_t* obj);
    static bool _lvIsChecked(lv_obj_t* obj);

private:
    ButtonConfig mButtonConfig;     ///< 按钮配置
    std::string mButtonText;        ///< 按钮文本
    bool mToggleMode;               ///< 切换模式
    bool mChecked;                  ///< 选中状态
};

} // namespace Gui