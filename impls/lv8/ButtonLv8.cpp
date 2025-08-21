#include "../../iface/Button.h"
#include "../../iface/ButtonConfig.h"
#include <lvgl.h>

namespace Gui {

// ==================== 静态方法实现 ====================

lv_obj_t* Button::_lvCreateButton(lv_obj_t* parent)
{
    return lv_button_create(parent);
}

void Button::_lvSetConfig(lv_obj_t* obj, const ButtonConfig& config)
{
    if (!obj) return;
    
    // 应用按钮样式
    lv_obj_set_style_radius(obj, config.buttonStyle.cornerRadius, LV_PART_MAIN);
    
    if (config.buttonStyle.borderWidth > 0) {
        lv_obj_set_style_border_width(obj, config.buttonStyle.borderWidth, LV_PART_MAIN);
        lv_obj_set_style_border_color(obj, lv_color_hex(config.buttonStyle.borderColor), LV_PART_MAIN);
    }
    
    if (config.buttonStyle.shadowWidth > 0) {
        lv_obj_set_style_shadow_width(obj, config.buttonStyle.shadowWidth, LV_PART_MAIN);
        lv_obj_set_style_shadow_color(obj, lv_color_hex(config.buttonStyle.shadowColor), LV_PART_MAIN);
        lv_obj_set_style_shadow_offset_x(obj, config.buttonStyle.shadowOffsetX, LV_PART_MAIN);
        lv_obj_set_style_shadow_offset_y(obj, config.buttonStyle.shadowOffsetY, LV_PART_MAIN);
    }
    
    // 应用按钮状态样式
    lv_obj_set_style_bg_color(obj, lv_color_hex(config.state.normalBgColor), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(obj, lv_color_hex(config.state.normalTextColor), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(obj, lv_color_hex(config.state.pressedBgColor), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_color(obj, lv_color_hex(config.state.pressedTextColor), LV_PART_MAIN | LV_STATE_PRESSED);
    
    lv_obj_set_style_bg_color(obj, lv_color_hex(config.state.disabledBgColor), LV_PART_MAIN | LV_STATE_DISABLED);
    lv_obj_set_style_text_color(obj, lv_color_hex(config.state.disabledTextColor), LV_PART_MAIN | LV_STATE_DISABLED);
    
    // 设置按钮文本
    if (!config.buttonText.empty()) {
        lv_obj_t* label = lv_label_create(obj);
        lv_label_set_text(label, config.buttonText.c_str());
        lv_obj_center(label);
    }
    
    // 设置切换模式
    if (config.toggleMode) {
        lv_obj_add_flag(obj, LV_OBJ_FLAG_CHECKABLE);
    }
    
    // 设置选中状态
    if (config.checked) {
        lv_obj_add_state(obj, LV_STATE_CHECKED);
    }
    
    // 设置可见性和启用状态
    if (!config.visible) {
        lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
    }
    
    if (!config.enabled) {
        lv_obj_add_state(obj, LV_STATE_DISABLED);
    }
    
    // 设置可点击性和焦点
    if (config.clickable) {
        lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
    }
    
    if (config.focusable) {
        lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
    }
}

void Button::_lvSetButtonText(lv_obj_t* obj, const std::string& text)
{
    if (!obj) return;
    
    // 在按钮中创建或更新标签
    lv_obj_t* label = lv_obj_get_child(obj, 0);
    if (!label || !lv_obj_check_type(label, &lv_label_class)) {
        label = lv_label_create(obj);
        lv_obj_center(label);
    }
    lv_label_set_text(label, text.c_str());
}

void Button::_lvSetButtonState(lv_obj_t* obj, lv_state_t state)
{
    if (!obj) return;
    lv_obj_clear_state(obj, LV_STATE_PRESSED | LV_STATE_FOCUSED | LV_STATE_DISABLED | LV_STATE_CHECKED);
    lv_obj_add_state(obj, state);
}

void Button::_lvClearButtonState(lv_obj_t* obj, lv_state_t state)
{
    if (!obj) return;
    lv_obj_clear_state(obj, state);
}

void Button::_lvAddButtonState(lv_obj_t* obj, lv_state_t state)
{
    if (!obj) return;
    lv_obj_add_state(obj, state);
}

void Button::_lvSetToggleMode(lv_obj_t* obj, bool enable)
{
    if (!obj) return;
    if (enable) {
        lv_obj_add_flag(obj, LV_OBJ_FLAG_CHECKABLE);
    } else {
        lv_obj_clear_flag(obj, LV_OBJ_FLAG_CHECKABLE);
    }
}

void Button::_lvSetChecked(lv_obj_t* obj, bool checked)
{
    if (!obj) return;
    if (checked) {
        lv_obj_add_state(obj, LV_STATE_CHECKED);
    } else {
        lv_obj_clear_state(obj, LV_STATE_CHECKED);
    }
}

void Button::_lvShowButton(lv_obj_t* obj)
{
    if (!obj) return;
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_HIDDEN);
}

void Button::_lvHideButton(lv_obj_t* obj)
{
    if (!obj) return;
    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
}

void Button::_lvEnableButton(lv_obj_t* obj)
{
    if (!obj) return;
    lv_obj_clear_state(obj, LV_STATE_DISABLED);
}

void Button::_lvDisableButton(lv_obj_t* obj)
{
    if (!obj) return;
    lv_obj_add_state(obj, LV_STATE_DISABLED);
}

std::string Button::_lvGetButtonText(lv_obj_t* obj)
{
    if (!obj) return "";
    
    lv_obj_t* label = lv_obj_get_child(obj, 0);
    if (label && lv_obj_check_type(label, &lv_label_class)) {
        return lv_label_get_text(label);
    }
    return "";
}

lv_state_t Button::_lvGetButtonState(lv_obj_t* obj)
{
    if (!obj) return LV_STATE_DEFAULT;
    return lv_obj_get_state(obj);
}

bool Button::_lvIsToggleMode(lv_obj_t* obj)
{
    if (!obj) return false;
    return lv_obj_has_flag(obj, LV_OBJ_FLAG_CHECKABLE);
}

bool Button::_lvIsChecked(lv_obj_t* obj)
{
    if (!obj) return false;
    return lv_obj_has_state(obj, LV_STATE_CHECKED);
}

} // namespace Gui