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

lv_obj_t* _lvCreateVStack(lv_obj_t* parent)
{
    return create_flex_container(parent, LV_FLEX_FLOW_COLUMN);
}

lv_obj_t* _lvCreateHStack(lv_obj_t* parent)
{
    return create_flex_container(parent, LV_FLEX_FLOW_ROW);
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

} // namespace Gui