#include "../../iface/Button.h"
#include "../../iface/ButtonConfig.h"
#include <lvgl.h>

namespace Gui {

// ==================== 静态辅助方法实现 ====================

lv_obj_t* Button::_lvCreateButton(lv_obj_t* parent)
{
    return lv_button_create(parent);
}

void Button::_lvSetConfig(lv_obj_t* obj, const ButtonConfig& config)
{
    if (!obj) return;
    
    // 设置按钮文本
    if (!config.buttonText.empty()) {
        lv_obj_t* label = lv_obj_get_child(obj, 0);
        if (label && lv_obj_check_type(label, &lv_label_class)) {
            lv_label_set_text(label, config.buttonText.c_str());
        } else {
            // 创建标签
            label = lv_label_create(obj);
            lv_label_set_text(label, config.buttonText.c_str());
            lv_obj_center(label);
        }
    }
    
    // 设置正常状态样式
    lv_obj_set_style_bg_color(obj, lv_color_hex(config.state.normalBgColor), LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(obj, lv_color_hex(config.state.normalTextColor), LV_STATE_DEFAULT);
    
    // 设置按下状态样式
    lv_obj_set_style_bg_color(obj, lv_color_hex(config.state.pressedBgColor), LV_STATE_PRESSED);
    lv_obj_set_style_text_color(obj, lv_color_hex(config.state.pressedTextColor), LV_STATE_PRESSED);
    
    // 设置禁用状态样式
    lv_obj_set_style_bg_color(obj, lv_color_hex(config.state.disabledBgColor), LV_STATE_DISABLED);
    lv_obj_set_style_text_color(obj, lv_color_hex(config.state.disabledTextColor), LV_STATE_DISABLED);
    
    // 设置样式属性
    lv_obj_set_style_radius(obj, config.buttonStyle.cornerRadius, LV_STATE_DEFAULT);
    
    if (config.buttonStyle.borderWidth > 0) {
        lv_obj_set_style_border_width(obj, config.buttonStyle.borderWidth, LV_STATE_DEFAULT);
        lv_obj_set_style_border_color(obj, lv_color_hex(config.buttonStyle.borderColor), LV_STATE_DEFAULT);
    }
    
    if (config.buttonStyle.shadowWidth > 0) {
        lv_obj_set_style_shadow_width(obj, config.buttonStyle.shadowWidth, LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_color(obj, lv_color_hex(config.buttonStyle.shadowColor), LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_offset_x(obj, config.buttonStyle.shadowOffsetX, LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_offset_y(obj, config.buttonStyle.shadowOffsetY, LV_STATE_DEFAULT);
    }
    
    // 设置状态属性
    if (config.toggleMode) {
        lv_obj_add_flag(obj, LV_OBJ_FLAG_CHECKABLE);
        if (config.checked) {
            lv_obj_add_state(obj, LV_STATE_CHECKED);
        } else {
            lv_obj_remove_state(obj, LV_STATE_CHECKED);
        }
    } else {
        lv_obj_remove_flag(obj, LV_OBJ_FLAG_CHECKABLE);
    }
    
    if (!config.clickable) {
        lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE);
    } else {
        lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
    }
    
    // LVGL v8 中焦点相关的设置方式不同，暂时跳过
    // if (!config.focusable) {
    //     // 在 LVGL v8 中可能使用不同的方式设置焦点
    // }
    
    if (!config.visible) {
        lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
    } else {
        lv_obj_remove_flag(obj, LV_OBJ_FLAG_HIDDEN);
    }
    
    if (!config.enabled) {
        lv_obj_add_state(obj, LV_STATE_DISABLED);
    } else {
        lv_obj_remove_state(obj, LV_STATE_DISABLED);
    }
}

} // namespace Gui