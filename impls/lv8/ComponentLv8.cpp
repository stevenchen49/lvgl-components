#include "../iface/Component.h"

#include <lvgl.h>

namespace Gui {

// ==================== 静态 LVGL 操作方法 ====================

lv_obj_t* Component::_lvCreateObject(lv_obj_t* parent)
{
    return lv_obj_create(parent);
}

lv_obj_t* Component::_lvSetPos(lv_obj_t* obj, const ComponentConfig::Pos& pos)
{
    if (obj) {
        lv_obj_set_pos(obj, pos.x, pos.y);
        if (pos.width > 0) lv_obj_set_width(obj, pos.width);
        if (pos.height > 0) lv_obj_set_height(obj, pos.height);
    }
    return obj;
}

lv_obj_t* Component::_lvSetLayout(lv_obj_t* obj, const ComponentConfig::Layout& layout)
{
    if (obj) {
        lv_obj_set_flex_flow(obj, layout.flexFlow);
        lv_obj_set_flex_align(obj, layout.mainPlace, layout.crossPlace, layout.trackPlace);
        if (layout.rowGap > 0) lv_obj_set_style_pad_row(obj, layout.rowGap, LV_PART_MAIN);
        if (layout.columnGap > 0) lv_obj_set_style_pad_column(obj, layout.columnGap, LV_PART_MAIN);
    }
    return obj;
}

lv_obj_t* Component::_lvSetStyle(lv_obj_t* obj, const ComponentConfig::Style& style)
{
    if (obj) {
        lv_obj_set_style_bg_color(obj, lv_color_hex(style.bgColor), LV_PART_MAIN);
        lv_obj_set_style_text_color(obj, lv_color_hex(style.textColor), LV_PART_MAIN);
        lv_obj_set_style_border_color(obj, lv_color_hex(style.borderColor), LV_PART_MAIN);
        lv_obj_set_style_bg_opa(obj, style.bgOpacity, LV_PART_MAIN);
        lv_obj_set_style_text_opa(obj, style.textOpacity, LV_PART_MAIN);
        lv_obj_set_style_border_opa(obj, style.borderOpacity, LV_PART_MAIN);
        lv_obj_set_style_border_width(obj, style.borderWidth, LV_PART_MAIN);
        lv_obj_set_style_radius(obj, style.radius, LV_PART_MAIN);
        lv_obj_set_style_pad_all(obj, style.padding, LV_PART_MAIN);
        lv_obj_set_style_margin_all(obj, style.margin, LV_PART_MAIN);
    }
    return obj;
}

lv_obj_t* Component::_lvSetText(lv_obj_t* obj, const ComponentConfig::Text& text)
{
    if (obj && text.enabled) {
        // 设置文本样式（所有对象都可以有文本样式）
        if (text.font) lv_obj_set_style_text_font(obj, text.font, LV_PART_MAIN);
        lv_obj_set_style_text_align(obj, text.align, LV_PART_MAIN);
        
        // 注意：文本内容设置需要根据具体对象类型来实现
        // 这里只设置样式，具体文本内容由子类实现
    }
    return obj;
}

lv_obj_t* Component::_lvSetEvent(lv_obj_t* obj, const ComponentConfig::Event& event)
{
    // TODO: 实现事件设置
    // 暂时注释掉，因为编译器无法识别 Event 结构体成员
    /*
    if (obj) {
        if (event.onClick) {
            lv_obj_add_event_cb(obj, _onClickCallback, LV_EVENT_CLICKED, nullptr);
        }
        if (event.onLongPress) {
            lv_obj_add_event_cb(obj, _onLongPressCallback, LV_EVENT_LONG_PRESSED, nullptr);
        }
        if (event.onFocus) {
            lv_obj_add_event_cb(obj, _onFocusCallback, LV_EVENT_FOCUSED, nullptr);
        }
        if (event.onBlur) {
            lv_obj_add_event_cb(obj, _onBlurCallback, LV_EVENT_DEFOCUSED, nullptr);
        }
    }
    */
    return obj;
}

lv_obj_t* Component::_lvSetAnimation(lv_obj_t* obj, const ComponentConfig::Animation& animation)
{
    if (obj && animation.enabled) {
        lv_obj_set_style_anim_time(obj, animation.duration, LV_PART_MAIN);
        // 注意：lv_obj_set_style_anim_speed 可能在某些 LVGL 版本中不可用
    }
    return obj;
}

// ==================== 事件回调 ====================

void Component::_onClickCallback(lv_event_t* e)
{
    // TODO: 实现点击回调
    /*
    Component* component = static_cast<Component*>(lv_event_get_user_data(e));
    if (component && component->mConfig.event.onClick) {
        component->mConfig.event.onClick(e);
    }
    */
}

void Component::_onLongPressCallback(lv_event_t* e)
{
    // TODO: 实现长按回调
    /*
    Component* component = static_cast<Component*>(lv_event_get_user_data(e));
    if (component && component->mConfig.event.onLongPress) {
        component->mConfig.event.onLongPress(e);
    }
    */
}

void Component::_onFocusCallback(lv_event_t* e)
{
    // TODO: 实现焦点回调
    /*
    Component* component = static_cast<Component*>(lv_event_get_user_data(e));
    if (component && component->mConfig.event.onFocus) {
        component->mConfig.event.onFocus(e);
    }
    */
}

void Component::_onBlurCallback(lv_event_t* e)
{
    // TODO: 实现失焦回调
    /*
    Component* component = static_cast<Component*>(lv_event_get_user_data(e));
    if (component && component->mConfig.event.onBlur) {
        component->mConfig.event.onBlur(e);
    }
    */
}

} // namespace Gui