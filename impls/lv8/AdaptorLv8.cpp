#include "Adaptor.h"

namespace Gui {

lv_obj_t* _lvCreateObj(lv_obj_t* parent)
{
    return lv_obj_create(parent);
}

// Generic helper to create a container with flex layout
static lv_obj_t* create_flex_container(lv_obj_t* parent, lv_flex_flow_t flow)
{
    lv_obj_t* cont = lv_obj_create(parent);
    lv_obj_set_size(cont, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_layout(cont, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(cont, flow);
    return cont;
}

void _lvSetStyleGap(lv_obj_t* obj, int gap, lv_flex_flow_t flow)
{
    if (flow == LV_FLEX_FLOW_COLUMN) {
        lv_obj_set_style_pad_row(obj, gap, LV_PART_MAIN);
    } else { // LV_FLEX_FLOW_ROW or ROW_WRAP
        lv_obj_set_style_pad_column(obj, gap, LV_PART_MAIN);
    }
}

void _lvSetFlexAlignment(lv_obj_t* obj, HorizontalAlignment align)
{
    lv_flex_align_t lv_align;
    switch (align) {
        case HorizontalAlignment::Leading:
            lv_align = LV_FLEX_ALIGN_START;
            break;
        case HorizontalAlignment::Center:
            lv_align = LV_FLEX_ALIGN_CENTER;
            break;
        case HorizontalAlignment::Trailing:
            lv_align = LV_FLEX_ALIGN_END;
            break;
    }
    lv_obj_set_style_flex_cross_place(obj, lv_align, LV_PART_MAIN);
}

void _lvSetFlexAlignment(lv_obj_t* obj, VerticalAlignment align)
{
    lv_flex_align_t lv_align;
    switch (align) {
        case VerticalAlignment::Top:
            lv_align = LV_FLEX_ALIGN_START;
            break;
        case VerticalAlignment::Center:
            lv_align = LV_FLEX_ALIGN_CENTER;
            break;
        case VerticalAlignment::Bottom:
            lv_align = LV_FLEX_ALIGN_END;
            break;
    }
    lv_obj_set_style_flex_cross_place(obj, lv_align, LV_PART_MAIN);
}

lv_obj_t* _lvCreateVStack(lv_obj_t* parent)
{
    return create_flex_container(parent, LV_FLEX_FLOW_COLUMN);
}

lv_obj_t* _lvCreateHStack(lv_obj_t* parent)
{
    return create_flex_container(parent, LV_FLEX_FLOW_ROW);
}

lv_obj_t* _lvCreateZStack(lv_obj_t* parent)
{
    lv_obj_t* cont = lv_obj_create(parent);
    lv_obj_set_size(cont, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    return cont;
}

lv_obj_t* _lvCreateLabel(lv_obj_t* parent)
{
    return lv_label_create(parent);
}

void _lvSetText(lv_obj_t* obj, const char* text)
{
    lv_label_set_text(obj, text);
}

lv_obj_t* _lvCreateButton(lv_obj_t* parent, const char* text)
{
    lv_obj_t* btn = lv_btn_create(parent);
    if (text) {
        lv_obj_t* label = lv_label_create(btn);
        lv_label_set_text(label, text);
        lv_obj_center(label);
    }
    return btn;
}

// Event handler for button clicks
static void button_event_cb(lv_event_t* e)
{
    auto* callback = static_cast<std::function<void()>*>(lv_event_get_user_data(e));
    if (callback && (*callback)) {
        (*callback)();
    }
}

void _lvSetOnClick(lv_obj_t* obj, std::function<void()> callback)
{
    // We need to store the callback on the heap so it persists.
    // The raw pointer is stored as user data. We must deallocate it when the object is deleted.
    auto* callback_ptr = new std::function<void()>(std::move(callback));
    lv_obj_add_event_cb(obj, button_event_cb, LV_EVENT_CLICKED, callback_ptr);

    // Add a cleanup event to delete the callback
    lv_obj_add_event_cb(obj, [](lv_event_t* e) {
        auto* cb = static_cast<std::function<void()>*>(lv_event_get_user_data(e));
        delete cb;
    }, LV_EVENT_DELETE, callback_ptr);
}

void _lvSetSize(lv_obj_t* obj, const Gui::Size& size)
{
    lv_obj_set_size(obj, size.width, size.height);
}

void _lvSetWidth(lv_obj_t* obj, int width)
{
    lv_obj_set_width(obj, width);
}

void _lvSetHeight(lv_obj_t* obj, int height)
{
    lv_obj_set_height(obj, height);
}

void _lvSetBgColor(lv_obj_t* obj, lv_color_t color)
{
    lv_obj_set_style_bg_color(obj, color, LV_PART_MAIN);
}

// --- Slider Implementation ---
lv_obj_t* _lvCreateSlider(lv_obj_t* parent)
{
    return lv_slider_create(parent);
}

void _lvSetSliderRange(lv_obj_t* obj, int min, int max)
{
    lv_slider_set_range(obj, min, max);
}

void _lvSetSliderValue(lv_obj_t* obj, int value, bool anim)
{
    lv_slider_set_value(obj, value, anim ? LV_ANIM_ON : LV_ANIM_OFF);
}

static void slider_event_cb(lv_event_t* e)
{
    lv_obj_t* slider = (lv_obj_t*)lv_event_get_target(e);
    auto* callback = static_cast<std::function<void(int)>*>(lv_event_get_user_data(e));
    if (callback && (*callback)) {
        int32_t value = lv_slider_get_value(slider);
        (*callback)(value);
    }
}

void _lvSetSliderOnValueChanged(lv_obj_t* obj, std::function<void(int)> callback)
{
    auto* callback_ptr = new std::function<void(int)>(std::move(callback));
    lv_obj_add_event_cb(obj, slider_event_cb, LV_EVENT_VALUE_CHANGED, callback_ptr);

    // Add a cleanup event to delete the callback
    lv_obj_add_event_cb(obj, [](lv_event_t* e) {
        auto* cb = static_cast<std::function<void(int)>*>(lv_event_get_user_data(e));
        delete cb;
    }, LV_EVENT_DELETE, callback_ptr);
}

// --- Switch Implementation ---
lv_obj_t* _lvCreateSwitch(lv_obj_t* parent)
{
    return lv_switch_create(parent);
}

void _lvSetSwitchState(lv_obj_t* obj, bool isOn)
{
    if (isOn) {
        lv_obj_add_state(obj, LV_STATE_CHECKED);
    } else {
        lv_obj_clear_state(obj, LV_STATE_CHECKED);
    }
}

static void switch_event_cb(lv_event_t* e)
{
    lv_obj_t* sw = (lv_obj_t*)lv_event_get_target(e);
    auto* callback = static_cast<std::function<void(bool)>*>(lv_event_get_user_data(e));
    if (callback && (*callback)) {
        bool is_on = lv_obj_has_state(sw, LV_STATE_CHECKED);
        (*callback)(is_on);
    }
}

void _lvSetSwitchOnToggle(lv_obj_t* obj, std::function<void(bool)> callback)
{
    auto* callback_ptr = new std::function<void(bool)>(std::move(callback));
    lv_obj_add_event_cb(obj, switch_event_cb, LV_EVENT_VALUE_CHANGED, callback_ptr);

    // Add a cleanup event to delete the callback
    lv_obj_add_event_cb(obj, [](lv_event_t* e) {
        auto* cb = static_cast<std::function<void(bool)>*>(lv_event_get_user_data(e));
        delete cb;
    }, LV_EVENT_DELETE, callback_ptr);
}

// --- Checkbox Implementation ---
lv_obj_t* _lvCreateCheckbox(lv_obj_t* parent)
{
    return lv_checkbox_create(parent);
}

void _lvSetCheckboxText(lv_obj_t* obj, const char* text)
{
    lv_checkbox_set_text(obj, text);
}

void _lvSetCheckboxState(lv_obj_t* obj, bool isChecked)
{
    if (isChecked) {
        lv_obj_add_state(obj, LV_STATE_CHECKED);
    } else {
        lv_obj_clear_state(obj, LV_STATE_CHECKED);
    }
}

static void checkbox_event_cb(lv_event_t* e)
{
    lv_obj_t* cbx = (lv_obj_t*)lv_event_get_target(e);
    auto* callback = static_cast<std::function<void(bool)>*>(lv_event_get_user_data(e));
    if (callback && (*callback)) {
        bool is_checked = lv_obj_has_state(cbx, LV_STATE_CHECKED);
        (*callback)(is_checked);
    }
}

void _lvSetCheckboxOnToggle(lv_obj_t* obj, std::function<void(bool)> callback)
{
    auto* callback_ptr = new std::function<void(bool)>(std::move(callback));
    lv_obj_add_event_cb(obj, checkbox_event_cb, LV_EVENT_VALUE_CHANGED, callback_ptr);

    // Add a cleanup event to delete the callback
    lv_obj_add_event_cb(obj, [](lv_event_t* e) {
        auto* cb = static_cast<std::function<void(bool)>*>(lv_event_get_user_data(e));
        delete cb;
    }, LV_EVENT_DELETE, callback_ptr);
}

// --- Image Implementation ---
lv_obj_t* _lvCreateImage(lv_obj_t* parent)
{
    return lv_img_create(parent);
}

void _lvSetImageSrc(lv_obj_t* obj, const lv_img_dsc_t* src)
{
    lv_img_set_src(obj, src);
}


} // namespace Gui