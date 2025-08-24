#include "../iface/Component.h"
#include "../iface/ComponentConfig.h"

#include <lvgl.h>

namespace Gui {

// ==================== 枚举转换函数 ====================

/**
 * @brief 将 FlexFlow 转换为 LVGL 类型
 */
static lv_flex_flow_t convertFlexFlow(ComponentConfig::FlexFlow flow) {
    switch (flow) {
        case ComponentConfig::FlexFlow::Row:           return LV_FLEX_FLOW_ROW;
        case ComponentConfig::FlexFlow::Column:        return LV_FLEX_FLOW_COLUMN;
        case ComponentConfig::FlexFlow::RowReverse:    return LV_FLEX_FLOW_ROW_REVERSE;
        case ComponentConfig::FlexFlow::ColumnReverse: return LV_FLEX_FLOW_COLUMN_REVERSE;
        default:                                       return LV_FLEX_FLOW_ROW;
    }
}

/**
 * @brief 将 FlexAlign 转换为 LVGL 类型
 */
static lv_flex_align_t convertFlexAlign(ComponentConfig::FlexAlign align) {
    switch (align) {
        case ComponentConfig::FlexAlign::Start:        return LV_FLEX_ALIGN_START;
        case ComponentConfig::FlexAlign::End:          return LV_FLEX_ALIGN_END;
        case ComponentConfig::FlexAlign::Center:       return LV_FLEX_ALIGN_CENTER;
        case ComponentConfig::FlexAlign::SpaceBetween: return LV_FLEX_ALIGN_SPACE_BETWEEN;
        case ComponentConfig::FlexAlign::SpaceAround:  return LV_FLEX_ALIGN_SPACE_AROUND;
        case ComponentConfig::FlexAlign::SpaceEvenly:  return LV_FLEX_ALIGN_SPACE_EVENLY;
        default:                                       return LV_FLEX_ALIGN_START;
    }
}

/**
 * @brief 将 TextAlign 转换为 LVGL 类型
 */
static lv_text_align_t convertTextAlign(ComponentConfig::TextAlign align) {
    switch (align) {
        case ComponentConfig::TextAlign::Left:   return LV_TEXT_ALIGN_LEFT;
        case ComponentConfig::TextAlign::Center: return LV_TEXT_ALIGN_CENTER;
        case ComponentConfig::TextAlign::Right:  return LV_TEXT_ALIGN_RIGHT;
        case ComponentConfig::TextAlign::Auto:   return LV_TEXT_ALIGN_AUTO;
        default:                                 return LV_TEXT_ALIGN_LEFT;
    }
}

/**
 * @brief 将 AnimPath 转换为 LVGL 动画路径回调
 */
static lv_anim_path_cb_t convertAnimPath(ComponentConfig::AnimPath path) {
    switch (path) {
        case ComponentConfig::AnimPath::Linear:    return lv_anim_path_linear;
        case ComponentConfig::AnimPath::EaseIn:    return lv_anim_path_ease_in;
        case ComponentConfig::AnimPath::EaseOut:   return lv_anim_path_ease_out;
        case ComponentConfig::AnimPath::EaseInOut: return lv_anim_path_ease_in_out;
        case ComponentConfig::AnimPath::Overshoot: return lv_anim_path_overshoot;
        case ComponentConfig::AnimPath::Bounce:    return lv_anim_path_bounce;
        default:                                   return lv_anim_path_ease_out;
    }
}

// ==================== 静态 LVGL 操作方法 ====================

lv_obj_t* Component::_lvCreateObject(lv_obj_t* parent)
{
    return lv_obj_create(parent);
}

void Component::_lvSetPos(lv_obj_t* obj, const ComponentConfig::Pos& pos)
{
    if (obj) {
        lv_obj_set_pos(obj, pos.x, pos.y);
        if (pos.width > 0) lv_obj_set_width(obj, pos.width);
        if (pos.height > 0) lv_obj_set_height(obj, pos.height);
    }
}

void Component::_lvSetLayout(lv_obj_t* obj, const ComponentConfig::Layout& layout)
{
    if (obj) {
        lv_obj_set_flex_flow(obj, convertFlexFlow(layout.flexFlow));
        lv_obj_set_flex_align(obj, 
            convertFlexAlign(layout.mainPlace), 
            convertFlexAlign(layout.crossPlace), 
            convertFlexAlign(layout.trackPlace));
        if (layout.rowGap > 0) lv_obj_set_style_pad_row(obj, layout.rowGap, LV_PART_MAIN);
        if (layout.columnGap > 0) lv_obj_set_style_pad_column(obj, layout.columnGap, LV_PART_MAIN);
    }
}









void Component::_lvSetVisable(lv_obj_t* obj, bool visible)
{
    if (!obj) return;
    
    if (visible) {
        lv_obj_clear_flag(obj, LV_OBJ_FLAG_HIDDEN);
    } else {
        lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
    }
}

void Component::_lvSetEnabled(lv_obj_t* obj, bool enabled)
{
    if (!obj) return;
    
    if (enabled) {
        lv_obj_clear_state(obj, LV_STATE_DISABLED);
    } else {
        lv_obj_add_state(obj, LV_STATE_DISABLED);
    }
}



} // namespace Gui