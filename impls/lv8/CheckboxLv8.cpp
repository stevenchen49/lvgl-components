#include "../../iface/Checkbox.h"
#include "../../iface/CheckboxConfig.h"
#include <lvgl.h>

namespace Gui {

// ==================== 静态辅助方法实现 ====================

lv_obj_t* Checkbox::_lvCreateCheckbox(lv_obj_t* parent)
{
    return lv_checkbox_create(parent);
}

void Checkbox::_lvSetConfig(lv_obj_t* obj, const CheckboxConfig& config)
{
    if (!obj) return;

    // 设置正常状态样式
    if (config.normal.bgColor == ColorConfig::Transparent) {
        lv_obj_set_style_bg_opa(obj, LV_OPA_TRANSP, LV_STATE_DEFAULT);
    } else {
        lv_obj_set_style_bg_color(obj, lv_color_hex(config.normal.bgColor), LV_STATE_DEFAULT);
        lv_obj_set_style_bg_opa(obj, LV_OPA_COVER, LV_STATE_DEFAULT);
    }
    lv_obj_set_style_border_color(obj, lv_color_hex(config.normal.borderColor), LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(obj, 1, LV_STATE_DEFAULT);
    lv_obj_set_style_radius(obj, 4, LV_STATE_DEFAULT);  // 圆角效果
    
    // 设置选中状态样式
    if (config.checked.bgColor == ColorConfig::Transparent) {
        lv_obj_set_style_bg_opa(obj, LV_OPA_TRANSP, LV_STATE_CHECKED);
    } else {
        lv_obj_set_style_bg_color(obj, lv_color_hex(config.checked.bgColor), LV_STATE_CHECKED);
        lv_obj_set_style_bg_opa(obj, LV_OPA_COVER, LV_STATE_CHECKED);
    }
    lv_obj_set_style_border_color(obj, lv_color_hex(config.checked.borderColor), LV_STATE_CHECKED);
    lv_obj_set_style_border_width(obj, 1, LV_STATE_CHECKED);
    lv_obj_set_style_radius(obj, 4, LV_STATE_CHECKED);  // 圆角效果
    
    // 设置禁用状态样式
    if (config.disabled.bgColor == ColorConfig::Transparent) {
        lv_obj_set_style_bg_opa(obj, LV_OPA_TRANSP, LV_STATE_DISABLED);
    } else {
        lv_obj_set_style_bg_color(obj, lv_color_hex(config.disabled.bgColor), LV_STATE_DISABLED);
        lv_obj_set_style_bg_opa(obj, LV_OPA_COVER, LV_STATE_DISABLED);
    }
    lv_obj_set_style_border_color(obj, lv_color_hex(config.disabled.borderColor), LV_STATE_DISABLED);
    lv_obj_set_style_border_width(obj, 1, LV_STATE_DISABLED);
    lv_obj_set_style_radius(obj, 4, LV_STATE_DISABLED);  // 圆角效果
    
    // 设置状态属性
    if (!config.clickable) {
        lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE);
    } else {
        lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
    }
    
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
    
    // 设置初始选中状态
    if (config.isChecked) {
        lv_obj_add_state(obj, LV_STATE_CHECKED);
    } else {
        lv_obj_remove_state(obj, LV_STATE_CHECKED);
    }
}

} // namespace Gui
