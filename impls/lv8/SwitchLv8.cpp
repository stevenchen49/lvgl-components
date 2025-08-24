#include "../../iface/Switch.h"
#include "../../iface/SwitchConfig.h"
#include <lvgl.h>

namespace Gui {

// ==================== 静态辅助方法实现 ====================

lv_obj_t* Switch::_lvCreateSwitch(lv_obj_t* parent)
{
    return lv_switch_create(parent);
}

void Switch::_lvSetConfig(lv_obj_t* obj, const SwitchConfig& config)
{
    if (!obj) return;

    // 设置开启状态样式
    lv_obj_set_style_bg_color(obj, lv_color_hex(config.on.trackColor), LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(obj, LV_OPA_COVER, LV_STATE_CHECKED);
    lv_obj_set_style_radius(obj, LV_RADIUS_CIRCLE, LV_STATE_CHECKED);
    
    // 设置关闭状态样式
    lv_obj_set_style_bg_color(obj, lv_color_hex(config.off.trackColor), LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(obj, LV_OPA_COVER, LV_STATE_DEFAULT);
    lv_obj_set_style_radius(obj, LV_RADIUS_CIRCLE, LV_STATE_DEFAULT);
    
    // 设置禁用状态样式
    lv_obj_set_style_bg_color(obj, lv_color_hex(config.disabled.trackColor), LV_STATE_DISABLED);
    lv_obj_set_style_bg_opa(obj, LV_OPA_COVER, LV_STATE_DISABLED);
    lv_obj_set_style_radius(obj, LV_RADIUS_CIRCLE, LV_STATE_DISABLED);
    
    // 设置滑块样式 - 开启状态
    lv_obj_set_style_bg_color(obj, lv_color_hex(config.on.knobColor), LV_STATE_CHECKED | LV_PART_KNOB);
    lv_obj_set_style_bg_opa(obj, LV_OPA_COVER, LV_STATE_CHECKED | LV_PART_KNOB);
    lv_obj_set_style_radius(obj, LV_RADIUS_CIRCLE, LV_STATE_CHECKED | LV_PART_KNOB);
    
    // 设置滑块样式 - 关闭状态
    lv_obj_set_style_bg_color(obj, lv_color_hex(config.off.knobColor), LV_PART_KNOB);
    lv_obj_set_style_bg_opa(obj, LV_OPA_COVER, LV_PART_KNOB);
    lv_obj_set_style_radius(obj, LV_RADIUS_CIRCLE, LV_PART_KNOB);
    
    // 设置滑块样式 - 禁用状态
    lv_obj_set_style_bg_color(obj, lv_color_hex(config.disabled.knobColor), LV_STATE_DISABLED | LV_PART_KNOB);
    lv_obj_set_style_bg_opa(obj, LV_OPA_COVER, LV_STATE_DISABLED | LV_PART_KNOB);
    lv_obj_set_style_radius(obj, LV_RADIUS_CIRCLE, LV_STATE_DISABLED | LV_PART_KNOB);
    
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
    
    // 设置初始状态
    if (config.isOn) {
        lv_obj_add_state(obj, LV_STATE_CHECKED);
    } else {
        lv_obj_remove_state(obj, LV_STATE_CHECKED);
    }
}

} // namespace Gui
