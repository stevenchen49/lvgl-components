#pragma once

#include "lvgl.h"
#include "Style.h"
#include <functional>

namespace Gui {

// Forward declarations for LVGL implementation functions
lv_obj_t* _lvCreateVStack(lv_obj_t* parent);
lv_obj_t* _lvCreateHStack(lv_obj_t* parent);
lv_obj_t* _lvCreateZStack(lv_obj_t* parent);

void _lvSetStyleGap(lv_obj_t* obj, int gap, lv_flex_flow_t flow);
void _lvSetFlexAlignment(lv_obj_t* obj, Layout::Horizontal align);
void _lvSetFlexAlignment(lv_obj_t* obj, Layout::Vertical align);

lv_obj_t* _lvCreateLabel(lv_obj_t* parent);
void _lvSetText(lv_obj_t* obj, const char* text);

lv_obj_t* _lvCreateButton(lv_obj_t* parent, const char* text);
void _lvSetOnClick(lv_obj_t* obj, std::function<void()> callback);

lv_obj_t* _lvCreateSlider(lv_obj_t* parent);
void _lvSetSliderRange(lv_obj_t* obj, int min, int max);
void _lvSetSliderValue(lv_obj_t* obj, int value, bool anim);
void _lvSetSliderOnValueChanged(lv_obj_t* obj, std::function<void(int)> callback);

lv_obj_t* _lvCreateSwitch(lv_obj_t* parent);
void _lvSetSwitchState(lv_obj_t* obj, bool isOn);
void _lvSetSwitchOnToggle(lv_obj_t* obj, std::function<void(bool)> callback);

lv_obj_t* _lvCreateCheckbox(lv_obj_t* parent);
void _lvSetCheckboxText(lv_obj_t* obj, const char* text);
void _lvSetCheckboxState(lv_obj_t* obj, bool isChecked);
void _lvSetCheckboxOnToggle(lv_obj_t* obj, std::function<void(bool)> callback);

lv_obj_t* _lvCreateImage(lv_obj_t* parent);
void _lvSetImageSrc(lv_obj_t* obj, const lv_img_dsc_t* src);

// Progress Bar functions
lv_obj_t* _lvCreateProgressBar(lv_obj_t* parent, int value);
void _lvSetProgressValue(lv_obj_t* obj, int value);
void _lvSetProgressRange(lv_obj_t* obj, int min, int max);
void _lvSetProgressOnValueChanged(lv_obj_t* obj, std::function<void(int)> callback);

// Spinner functions
lv_obj_t* _lvCreateSpinner(lv_obj_t* parent);
void _lvSetSpinnerTime(lv_obj_t* obj, uint32_t time);
void _lvSetSpinnerAngle(lv_obj_t* obj, uint16_t angle);

// Text Area functions
lv_obj_t* _lvCreateTextArea(lv_obj_t* parent, const char* placeholder);
void _lvSetTextAreaText(lv_obj_t* obj, const char* text);
void _lvSetTextAreaPlaceholder(lv_obj_t* obj, const char* placeholder);
void _lvSetTextAreaOnTextChanged(lv_obj_t* obj, std::function<void(const std::string&)> callback);
void _lvSetTextAreaMaxLength(lv_obj_t* obj, uint32_t max_len);

// List functions
lv_obj_t* _lvCreateList(lv_obj_t* parent);
void _lvAddListItem(lv_obj_t* obj, const char* text);
void _lvSetListOnItemSelected(lv_obj_t* obj, std::function<void(int, const std::string&)> callback);

// Bar functions
lv_obj_t* _lvCreateBar(lv_obj_t* parent, int value);
void _lvSetBarValue(lv_obj_t* obj, int value);
void _lvSetBarRange(lv_obj_t* obj, int min, int max);
void _lvSetBarOnValueChanged(lv_obj_t* obj, std::function<void(int)> callback);

void _lvSetSize(lv_obj_t* obj, const Gui::Size& size);
void _lvSetWidth(lv_obj_t* obj, int width);
void _lvSetHeight(lv_obj_t* obj, int height);
void _lvSetBgColor(lv_obj_t* obj, lv_color_t color);

} // namespace Gui