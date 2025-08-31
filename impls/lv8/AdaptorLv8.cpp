#include "../../iface/gui/Adaptor.h"
#include "../../iface/gui/style/Color.h"

#include <lvgl.h>
#include <unistd.h>

namespace gui {
namespace adaptor {

int _lvPreinit()
{ 
    // do nothing
    return 0;
}

int _lvInit()
{
    lv_init();
    return 0;
}

void _lvDeinit()
{
    return;
}

void _lvLoop()
{
    while (true) {
        lv_timer_handler();
        usleep(5000);
    }
    return;
}

void _lvAsyncCall(std::function<void()> task)
{
    auto *taskPtr = new std::function<void()>(std::move(task));

    lv_async_call([](void* user_data) {
        auto* actualTask = static_cast<std::function<void()>*>(user_data);
        try {
            (*actualTask)();
        } catch (...) {
            // TODO: LOG ERROR
        }
        delete actualTask;
    }, taskPtr);
}

lv_obj_t* _lvCreateObj(lv_obj_t* parent)
{
    return lv_obj_create(parent);
}

void _lvDestroyObj(lv_obj_t* obj)
{
    lv_obj_del(obj);
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

void _lvSetFlexAlignment(lv_obj_t* obj, gui::style::Layout::Horizontal align)
{
    lv_flex_align_t lv_align;
    switch (align) {
        case gui::style::Layout::Horizontal::Leading: {
            lv_align = LV_FLEX_ALIGN_START;
        }
        break;
        case gui::style::Layout::Horizontal::Center: {
            lv_align = LV_FLEX_ALIGN_CENTER;
        }
        break;
        case gui::style::Layout::Horizontal::Trailing: {
            lv_align = LV_FLEX_ALIGN_END;
        }
        break;
    }
    lv_obj_set_style_flex_cross_place(obj, lv_align, LV_PART_MAIN);
}

void _lvSetFlexAlignment(lv_obj_t* obj, gui::style::Layout::Vertical align)
{
    lv_flex_align_t lv_align;
    switch (align) {
        case gui::style::Layout::Vertical::Top: {
            lv_align = LV_FLEX_ALIGN_START;
        }
        break;
        case gui::style::Layout::Vertical::Center: {
            lv_align = LV_FLEX_ALIGN_CENTER;
        }
        break;
        case gui::style::Layout::Vertical::Bottom: {
            lv_align = LV_FLEX_ALIGN_END;
        }
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

lv_obj_t* _lvCreateButton(lv_obj_t* parent)
{
    return lv_btn_create(parent);
}

void _lvSetButtonText(lv_obj_t* obj, const char* text)
{
    if (!text) return;
    
    // Check if button already has a label
    lv_obj_t* label = lv_obj_get_child(obj, 0);
    if (label && lv_obj_check_type(label, &lv_label_class)) {
        lv_label_set_text(label, text);
    } else {
        // Create new label
        label = lv_label_create(obj);
        lv_label_set_text(label, text);
        lv_obj_center(label);
    }
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

void _lvSetSize(lv_obj_t* obj, const gui::style::Size& size)
{
    lv_obj_set_size(obj, size.width, size.height);
}

void _lvSetTextColor(lv_obj_t* obj, lv_color_t color)
{
    lv_obj_set_style_text_color(obj, color, LV_PART_MAIN);
}

void _lvSetTextColor(lv_obj_t* obj, const gui::style::Color& color)
{
    lv_color_t lv_color = lv_color_hex(color.value);
    lv_obj_set_style_text_color(obj, lv_color, LV_PART_MAIN);
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

void _lvSetBgColor(lv_obj_t* obj, const gui::style::Color& color)
{
    lv_color_t lv_color = lv_color_hex(color.value);
    lv_obj_set_style_bg_color(obj, lv_color, LV_PART_MAIN);
}

// Progress Bar implementations
lv_obj_t* _lvCreateProgressBar(lv_obj_t* parent, int value)
{
    lv_obj_t* bar = lv_bar_create(parent);
    lv_bar_set_value(bar, value, LV_ANIM_ON);
    return bar;
}

void _lvSetProgressValue(lv_obj_t* obj, int value)
{
    lv_bar_set_value(obj, value, LV_ANIM_ON);
}

void _lvSetProgressRange(lv_obj_t* obj, int min, int max)
{
    lv_bar_set_range(obj, min, max);
}

static void progress_event_cb(lv_event_t* e)
{
    auto* callback = static_cast<std::function<void(int)>*>(lv_event_get_user_data(e));
    if (callback && (*callback)) {
        lv_obj_t* obj = (lv_obj_t*)lv_event_get_target(e);
        int value = lv_bar_get_value(obj);
        (*callback)(value);
    }
}

void _lvSetProgressOnValueChanged(lv_obj_t* obj, std::function<void(int)> callback)
{
    auto* callback_ptr = new std::function<void(int)>(std::move(callback));
    lv_obj_add_event_cb(obj, progress_event_cb, LV_EVENT_VALUE_CHANGED, callback_ptr);

    lv_obj_add_event_cb(obj, [](lv_event_t* e) {
        auto* cb = static_cast<std::function<void(int)>*>(lv_event_get_user_data(e));
        delete cb;
    }, LV_EVENT_DELETE, callback_ptr);
}

// Spinner implementations
lv_obj_t* _lvCreateSpinner(lv_obj_t* parent)
{
    return lv_spinner_create(parent);
}

void _lvSetSpinnerTime(lv_obj_t* obj, uint32_t time)
{
    // Note: LVGL spinner doesn't have a direct API to set animation time
    // We'll use the default animation time
}

void _lvSetSpinnerAngle(lv_obj_t* obj, uint16_t angle)
{
    // Note: LVGL spinner doesn't have a direct API to set angle
    // We'll use the default angle
}

// Text Area implementations
lv_obj_t* _lvCreateTextArea(lv_obj_t* parent, const char* placeholder)
{
    lv_obj_t* ta = lv_textarea_create(parent);
    if (placeholder) {
        lv_textarea_set_placeholder_text(ta, placeholder);
    }
    return ta;
}

void _lvSetTextAreaText(lv_obj_t* obj, const char* text)
{
    lv_textarea_set_text(obj, text);
}

void _lvSetTextAreaPlaceholder(lv_obj_t* obj, const char* placeholder)
{
    lv_textarea_set_placeholder_text(obj, placeholder);
}

static void textarea_event_cb(lv_event_t* e)
{
    auto* callback = static_cast<std::function<void(const std::string&)>*>(lv_event_get_user_data(e));
    if (callback && (*callback)) {
        lv_obj_t* obj = (lv_obj_t*)lv_event_get_target(e);
        const char* text = lv_textarea_get_text(obj);
        (*callback)(std::string(text));
    }
}

void _lvSetTextAreaOnTextChanged(lv_obj_t* obj, std::function<void(const std::string&)> callback)
{
    auto* callback_ptr = new std::function<void(const std::string&)>(std::move(callback));
    lv_obj_add_event_cb(obj, textarea_event_cb, LV_EVENT_VALUE_CHANGED, callback_ptr);

    lv_obj_add_event_cb(obj, [](lv_event_t* e) {
        auto* cb = static_cast<std::function<void(const std::string&)>*>(lv_event_get_user_data(e));
        delete cb;
    }, LV_EVENT_DELETE, callback_ptr);
}

void _lvSetTextAreaMaxLength(lv_obj_t* obj, uint32_t max_len)
{
    lv_textarea_set_max_length(obj, max_len);
}

// List implementations
lv_obj_t* _lvCreateList(lv_obj_t* parent)
{
    return lv_list_create(parent);
}

void _lvAddListItem(lv_obj_t* obj, const char* text)
{
    lv_list_add_text(obj, text);
}

static void list_event_cb(lv_event_t* e)
{
    auto* callback = static_cast<std::function<void(int, const std::string&)>*>(lv_event_get_user_data(e));
    if (callback && (*callback)) {
        lv_obj_t* obj = (lv_obj_t*)lv_event_get_target(e);
        lv_obj_t* list_item = (lv_obj_t*)lv_event_get_target(e);
        // Note: This is a simplified implementation. In a real scenario, you'd need to track item indices.
        (*callback)(0, "List item clicked");
    }
}

void _lvSetListOnItemSelected(lv_obj_t* obj, std::function<void(int, const std::string&)> callback)
{
    auto* callback_ptr = new std::function<void(int, const std::string&)>(std::move(callback));
    lv_obj_add_event_cb(obj, list_event_cb, LV_EVENT_CLICKED, callback_ptr);

    lv_obj_add_event_cb(obj, [](lv_event_t* e) {
        auto* cb = static_cast<std::function<void(int, const std::string&)>*>(lv_event_get_user_data(e));
        delete cb;
    }, LV_EVENT_DELETE, callback_ptr);
}

// Bar implementations
lv_obj_t* _lvCreateBar(lv_obj_t* parent, int value)
{
    lv_obj_t* bar = lv_bar_create(parent);
    lv_bar_set_value(bar, value, LV_ANIM_ON);
    return bar;
}

void _lvSetBarValue(lv_obj_t* obj, int value)
{
    lv_bar_set_value(obj, value, LV_ANIM_ON);
}

void _lvSetBarRange(lv_obj_t* obj, int min, int max)
{
    lv_bar_set_range(obj, min, max);
}

static void bar_event_cb(lv_event_t* e)
{
    auto* callback = static_cast<std::function<void(int)>*>(lv_event_get_user_data(e));
    if (callback && (*callback)) {
        lv_obj_t* obj = (lv_obj_t*)lv_event_get_target(e);
        int value = lv_bar_get_value(obj);
        (*callback)(value);
    }
}

void _lvSetBarOnValueChanged(lv_obj_t* obj, std::function<void(int)> callback)
{
    auto* callback_ptr = new std::function<void(int)>(std::move(callback));
    lv_obj_add_event_cb(obj, bar_event_cb, LV_EVENT_VALUE_CHANGED, callback_ptr);

    lv_obj_add_event_cb(obj, [](lv_event_t* e) {
        auto* cb = static_cast<std::function<void(int)>*>(lv_event_get_user_data(e));
        delete cb;
    }, LV_EVENT_DELETE, callback_ptr);
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

} // namespace adaptor
} // namespace gui