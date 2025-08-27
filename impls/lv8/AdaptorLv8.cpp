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

void _lvSetFlexAlignment(lv_obj_t* obj, Layout::Horizontal align)
{
    lv_flex_align_t lv_align;
    switch (align) {
        case Layout::Horizontal::Leading:
            lv_align = LV_FLEX_ALIGN_START;
            break;
        case Layout::Horizontal::Center:
            lv_align = LV_FLEX_ALIGN_CENTER;
            break;
        case Layout::Horizontal::Trailing:
            lv_align = LV_FLEX_ALIGN_END;
            break;
    }
    lv_obj_set_style_flex_cross_place(obj, lv_align, LV_PART_MAIN);
}

void _lvSetFlexAlignment(lv_obj_t* obj, Layout::Vertical align)
{
    lv_flex_align_t lv_align;
    switch (align) {
        case Layout::Vertical::Top:
            lv_align = LV_FLEX_ALIGN_START;
            break;
        case Layout::Vertical::Center:
            lv_align = LV_FLEX_ALIGN_CENTER;
            break;
        case Layout::Vertical::Bottom:
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

void _lvSetText(lv_obj_t* obj, const std::string& text)
{
    lv_label_set_text(obj, text.c_str());
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

lv_obj_t* _lvCreateButton(lv_obj_t* parent)
{
    return lv_btn_create(parent);
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

// 新的简化样式系统实现
void _lvSetStyle(lv_obj_t* obj, const StyleProperty& prop)
{
    // 将我们的枚举转换为 LVGL 的选择器
    lv_style_selector_t selector = LV_PART_MAIN;
    
    // 根据 Part 类型转换
    switch (prop.part) {
        case Part::Type::Main: selector |= LV_PART_MAIN; break;
        case Part::Type::Scrollbar: selector |= LV_PART_SCROLLBAR; break;
        case Part::Type::Indicator: selector |= LV_PART_INDICATOR; break;
        case Part::Type::Knob: selector |= LV_PART_KNOB; break;
        case Part::Type::Selected: selector |= LV_PART_SELECTED; break;
        case Part::Type::Items: selector |= LV_PART_ITEMS; break;
        case Part::Type::Cursor: selector |= LV_PART_CURSOR; break;
        case Part::Type::Any: selector |= LV_PART_ANY; break;
        default: selector |= LV_PART_MAIN; break;
    }
    
    // 根据 State 类型转换
    switch (prop.state) {
        case State::Type::Normal: selector |= LV_STATE_DEFAULT; break;
        case State::Type::Checked: selector |= LV_STATE_CHECKED; break;
        case State::Type::Focused: selector |= LV_STATE_FOCUSED; break;
        case State::Type::Pressed: selector |= LV_STATE_PRESSED; break;
        case State::Type::Disabled: selector |= LV_STATE_DISABLED; break;
        case State::Type::Hovered: selector |= LV_STATE_HOVERED; break;
        case State::Type::Edited: selector |= LV_STATE_EDITED; break;
        case State::Type::Any: selector |= LV_STATE_ANY; break;
    }
    
    // 根据属性类型设置样式
    switch (prop.type) {
        case StyleProperty::Type::Width:
            lv_obj_set_style_width(obj, prop.value.intValue, selector);
            break;
        case StyleProperty::Type::Height:
            lv_obj_set_style_height(obj, prop.value.intValue, selector);
            break;
        case StyleProperty::Type::TextColor:
            lv_obj_set_style_text_color(obj, lv_color_hex(prop.value.colorValue), selector);
            break;
        case StyleProperty::Type::BackgroundColor:
            lv_obj_set_style_bg_color(obj, lv_color_hex(prop.value.colorValue), selector);
            break;
        case StyleProperty::Type::BackgroundOpacity:
            lv_obj_set_style_bg_opa(obj, prop.value.intValue, selector);
            break;
        case StyleProperty::Type::BorderWidth:
            lv_obj_set_style_border_width(obj, prop.value.intValue, selector);
            break;
        case StyleProperty::Type::BorderColor:
            lv_obj_set_style_border_color(obj, lv_color_hex(prop.value.colorValue), selector);
            break;
        case StyleProperty::Type::BorderRadius:
            lv_obj_set_style_radius(obj, prop.value.radiusValue.topLeft, selector);
            break;
        case StyleProperty::Type::Padding: {
            const auto& padding = prop.value.paddingValue;
            lv_obj_set_style_pad_top(obj, padding.top, selector);
            lv_obj_set_style_pad_bottom(obj, padding.bottom, selector);
            lv_obj_set_style_pad_left(obj, padding.left, selector);
            lv_obj_set_style_pad_right(obj, padding.right, selector);
            break;
        }
        case StyleProperty::Type::Margin: {
            const auto& margin = prop.value.marginValue;
            lv_obj_set_style_margin_top(obj, margin.top, selector);
            lv_obj_set_style_margin_bottom(obj, margin.bottom, selector);
            lv_obj_set_style_margin_left(obj, margin.left, selector);
            lv_obj_set_style_margin_right(obj, margin.right, selector);
            break;
        }
        case StyleProperty::Type::Shadow: {
            const auto& shadow = prop.value.shadowValue;
            lv_obj_set_style_shadow_width(obj, shadow.blur, selector);
            lv_obj_set_style_shadow_ofs_x(obj, shadow.offsetX, selector);
            lv_obj_set_style_shadow_ofs_y(obj, shadow.offsetY, selector);
            lv_obj_set_style_shadow_spread(obj, shadow.spread, selector);
            lv_obj_set_style_shadow_color(obj, lv_color_hex(shadow.color), selector);
            lv_obj_set_style_shadow_opa(obj, shadow.opacity, selector);
            break;
        }
        case StyleProperty::Type::Opacity:
            lv_obj_set_style_opa(obj, prop.value.intValue, selector);
            break;
        case StyleProperty::Type::TextSize: {
            // 将我们的字体大小枚举转换为 LVGL 字体
            const lv_font_t* font = &lv_font_montserrat_14; // 默认字体
            switch (prop.value.fontSizeValue) {
                case Style::Font::Size::XSmall: font = &lv_font_montserrat_12; break;  // 使用12作为最小
                case Style::Font::Size::Small: font = &lv_font_montserrat_12; break;
                case Style::Font::Size::Medium: font = &lv_font_montserrat_14; break;
                case Style::Font::Size::Large: font = &lv_font_montserrat_16; break;
                case Style::Font::Size::XLarge: font = &lv_font_montserrat_20; break;
                case Style::Font::Size::XXLarge: font = &lv_font_montserrat_24; break;
            }
            lv_obj_set_style_text_font(obj, font, selector);
            break;
        }
        case StyleProperty::Type::TextAlign: {
            lv_text_align_t align = LV_TEXT_ALIGN_LEFT;
            switch (prop.value.textAlignValue) {
                case Style::Text::Align::Left: align = LV_TEXT_ALIGN_LEFT; break;
                case Style::Text::Align::Center: align = LV_TEXT_ALIGN_CENTER; break;
                case Style::Text::Align::Right: align = LV_TEXT_ALIGN_RIGHT; break;
                case Style::Text::Align::Justify: align = LV_TEXT_ALIGN_LEFT; break; // LVGL 没有 justify
            }
            lv_obj_set_style_text_align(obj, align, selector);
            break;
        }
        case StyleProperty::Type::TextDecoration: {
            lv_text_decor_t decor = LV_TEXT_DECOR_NONE;
            switch (prop.value.textDecorationValue) {
                case Style::Text::Decoration::None: decor = LV_TEXT_DECOR_NONE; break;
                case Style::Text::Decoration::Underline: decor = LV_TEXT_DECOR_UNDERLINE; break;
                case Style::Text::Decoration::Strikethrough: decor = LV_TEXT_DECOR_STRIKETHROUGH; break;
            }
            lv_obj_set_style_text_decor(obj, decor, selector);
            break;
        }
        default:
            // 未支持的属性类型，忽略
            break;
    }
}

// State management functions
void _lvAddState(lv_obj_t* obj, lv_state_t state)
{
    lv_obj_add_state(obj, state);
}

void _lvRemoveState(lv_obj_t* obj, lv_state_t state)
{
    lv_obj_remove_state(obj, state);
}

// Layout functions
void _lvSetStyleGap(lv_obj_t* obj, int gap, int flex_flow)
{
    if (flex_flow == LV_FLEX_FLOW_COLUMN) {
        lv_obj_set_style_pad_row(obj, gap, LV_PART_MAIN);
    } else {
        lv_obj_set_style_pad_column(obj, gap, LV_PART_MAIN);
    }
}

// _lvSetFlexAlignment function already defined above

// List functions
void _lvSetListOnItemSelected(lv_obj_t* obj, std::function<void(int, const std::string&)> callback)
{
    _lvSetListCallback(obj, callback);
}

// Bar functions  
void _lvSetBarOnValueChanged(lv_obj_t* obj, std::function<void(int)> callback)
{
    _lvSetBarCallback(obj, callback);
}

// Progress Bar implementations
lv_obj_t* _lvCreateProgressBar(lv_obj_t* parent, int value)
{
    lv_obj_t* bar = lv_bar_create(parent);
    lv_bar_set_value(bar, value, LV_ANIM_ON);
    return bar;
}

lv_obj_t* _lvCreateProgressBar(lv_obj_t* parent)
{
    return lv_bar_create(parent);
}

void _lvSetProgressBarValue(lv_obj_t* obj, int value)
{
    lv_bar_set_value(obj, value, LV_ANIM_ON);
}

void _lvSetProgressBarRange(lv_obj_t* obj, int min, int max)
{
    lv_bar_set_range(obj, min, max);
}

void _lvSetProgressBarCallback(lv_obj_t* obj, std::function<void(int)> callback)
{
    auto* callback_ptr = new std::function<void(int)>(std::move(callback));
    lv_obj_add_event_cb(obj, [](lv_event_t* e) {
        auto* cb = static_cast<std::function<void(int)>*>(lv_event_get_user_data(e));
        if (cb && (*cb)) {
            lv_obj_t* bar = (lv_obj_t*)lv_event_get_target(e);
            int value = lv_bar_get_value(bar);
            (*cb)(value);
        }
    }, LV_EVENT_VALUE_CHANGED, callback_ptr);
    
    lv_obj_add_event_cb(obj, [](lv_event_t* e) {
        auto* cb = static_cast<std::function<void(int)>*>(lv_event_get_user_data(e));
        delete cb;
    }, LV_EVENT_DELETE, callback_ptr);
}

void _lvSetBarCallback(lv_obj_t* obj, std::function<void(int)> callback)
{
    _lvSetProgressBarCallback(obj, callback);
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

void _lvSetSpinnerTime(lv_obj_t* obj, int time)
{
    // Note: LVGL spinner doesn't have a direct API to set animation time
    // We'll use the default animation time
}

void _lvSetSpinnerAngle(lv_obj_t* obj, uint16_t angle)
{
    // Note: LVGL spinner doesn't have a direct API to set angle
    // We'll use the default angle
}

void _lvSetSpinnerAngle(lv_obj_t* obj, int angle)
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

lv_obj_t* _lvCreateTextArea(lv_obj_t* parent)
{
    return lv_textarea_create(parent);
}

void _lvSetTextAreaText(lv_obj_t* obj, const char* text)
{
    lv_textarea_set_text(obj, text);
}

void _lvSetTextAreaPlaceholder(lv_obj_t* obj, const char* placeholder)
{
    lv_textarea_set_placeholder_text(obj, placeholder);
}

void _lvSetTextAreaPlaceholder(lv_obj_t* obj, const std::string& placeholder)
{
    lv_textarea_set_placeholder_text(obj, placeholder.c_str());
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

void _lvSetTextAreaMaxLength(lv_obj_t* obj, int max_len)
{
    lv_textarea_set_max_length(obj, static_cast<uint32_t>(max_len));
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

void _lvAddListItem(lv_obj_t* obj, const std::string& text)
{
    lv_list_add_text(obj, text.c_str());
}

void _lvSetListCallback(lv_obj_t* obj, std::function<void(int, const std::string&)> callback)
{
    auto* callback_ptr = new std::function<void(int, const std::string&)>(std::move(callback));
    lv_obj_add_event_cb(obj, [](lv_event_t* e) {
        auto* cb = static_cast<std::function<void(int, const std::string&)>*>(lv_event_get_user_data(e));
        if (cb && (*cb)) {
            // Note: This is a simplified implementation. In a real scenario, you'd need to track item indices.
            (*cb)(0, "List item clicked");
        }
    }, LV_EVENT_CLICKED, callback_ptr);
    
    lv_obj_add_event_cb(obj, [](lv_event_t* e) {
        auto* cb = static_cast<std::function<void(int, const std::string&)>*>(lv_event_get_user_data(e));
        delete cb;
    }, LV_EVENT_DELETE, callback_ptr);
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

// _lvSetListOnItemSelected already defined above

// Bar implementations
lv_obj_t* _lvCreateBar(lv_obj_t* parent, int value)
{
    lv_obj_t* bar = lv_bar_create(parent);
    lv_bar_set_value(bar, value, LV_ANIM_ON);
    return bar;
}

lv_obj_t* _lvCreateBar(lv_obj_t* parent)
{
    return lv_bar_create(parent);
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

// _lvSetBarOnValueChanged already defined above

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

void _lvSetSliderValue(lv_obj_t* obj, int value)
{
    lv_slider_set_value(obj, value, LV_ANIM_OFF);
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

void _lvSetCheckboxText(lv_obj_t* obj, const std::string& text)
{
    lv_checkbox_set_text(obj, text.c_str());
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