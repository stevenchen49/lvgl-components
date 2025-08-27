#pragma once

#include "Style.h"
#include "lvgl.h"
#include <string>
#include <functional>

namespace Gui {

// Basic object creation functions
lv_obj_t* _lvCreateLabel(lv_obj_t* parent);
lv_obj_t* _lvCreateButton(lv_obj_t* parent);
lv_obj_t* _lvCreateSlider(lv_obj_t* parent);
lv_obj_t* _lvCreateSwitch(lv_obj_t* parent);
lv_obj_t* _lvCreateCheckbox(lv_obj_t* parent);
lv_obj_t* _lvCreateImage(lv_obj_t* parent);
lv_obj_t* _lvCreateProgressBar(lv_obj_t* parent);
lv_obj_t* _lvCreateSpinner(lv_obj_t* parent);
lv_obj_t* _lvCreateTextArea(lv_obj_t* parent);
lv_obj_t* _lvCreateList(lv_obj_t* parent);
lv_obj_t* _lvCreateBar(lv_obj_t* parent);

// Container functions
lv_obj_t* _lvCreateVStack(lv_obj_t* parent);
lv_obj_t* _lvCreateHStack(lv_obj_t* parent);
lv_obj_t* _lvCreateZStack(lv_obj_t* parent);

// Text functions
void _lvSetText(lv_obj_t* obj, const std::string& text);

// Slider functions
void _lvSetSliderRange(lv_obj_t* obj, int min, int max);
void _lvSetSliderValue(lv_obj_t* obj, int value);
void _lvSetSliderCallback(lv_obj_t* obj, std::function<void(int)> callback);

// Switch functions
void _lvSetSwitchState(lv_obj_t* obj, bool state);
void _lvSetSwitchCallback(lv_obj_t* obj, std::function<void(bool)> callback);

// Checkbox functions
void _lvSetCheckboxText(lv_obj_t* obj, const std::string& text);
void _lvSetCheckboxState(lv_obj_t* obj, bool state);
void _lvSetCheckboxCallback(lv_obj_t* obj, std::function<void(bool)> callback);

// Image functions
void _lvSetImageSrc(lv_obj_t* obj, const std::string& src);
void _lvSetImageSrc(lv_obj_t* obj, const lv_img_dsc_t* src);

// Progress Bar functions
void _lvSetProgressBarValue(lv_obj_t* obj, int value);
void _lvSetProgressBarRange(lv_obj_t* obj, int min, int max);
void _lvSetProgressBarCallback(lv_obj_t* obj, std::function<void(int)> callback);

// Spinner functions
void _lvSetSpinnerTime(lv_obj_t* obj, int time);
void _lvSetSpinnerAngle(lv_obj_t* obj, int angle);

// Text Area functions
void _lvSetTextAreaText(lv_obj_t* obj, const std::string& text);
void _lvSetTextAreaPlaceholder(lv_obj_t* obj, const std::string& placeholder);
void _lvSetTextAreaMaxLength(lv_obj_t* obj, int maxLength);
void _lvSetTextAreaCallback(lv_obj_t* obj, std::function<void(const std::string&)> callback);

// List functions
void _lvAddListItem(lv_obj_t* obj, const std::string& item);
void _lvSetListCallback(lv_obj_t* obj, std::function<void(int, const std::string&)> callback);

// Bar functions
void _lvSetBarValue(lv_obj_t* obj, int value);
void _lvSetBarRange(lv_obj_t* obj, int min, int max);
void _lvSetBarCallback(lv_obj_t* obj, std::function<void(int)> callback);

// Event functions
void _lvSetOnClick(lv_obj_t* obj, std::function<void()> callback);

// Layout functions
void _lvSetFlexLayout(lv_obj_t* obj, bool isColumn);
void _lvSetSpacing(lv_obj_t* obj, int spacing);
void _lvSetAlignment(lv_obj_t* obj, Layout::Horizontal h, Layout::Vertical v);
void _lvSetStyleGap(lv_obj_t* obj, int gap, int flex_flow);
void _lvSetFlexAlignment(lv_obj_t* obj, Layout::Vertical align);
void _lvSetFlexAlignment(lv_obj_t* obj, Layout::Horizontal align);

// Additional callback functions
void _lvSetSliderOnValueChanged(lv_obj_t* obj, std::function<void(int)> callback);
void _lvSetSwitchOnToggle(lv_obj_t* obj, std::function<void(bool)> callback);
void _lvSetCheckboxOnToggle(lv_obj_t* obj, std::function<void(bool)> callback);
void _lvSetProgressOnValueChanged(lv_obj_t* obj, std::function<void(int)> callback);
void _lvSetTextAreaOnTextChanged(lv_obj_t* obj, std::function<void(const std::string&)> callback);

// Compatibility functions for old interfaces
void _lvSetProgressValue(lv_obj_t* obj, int value);
void _lvSetProgressRange(lv_obj_t* obj, int min, int max);

// List functions
void _lvSetListOnItemSelected(lv_obj_t* obj, std::function<void(int, const std::string&)> callback);

// Bar functions  
void _lvSetBarOnValueChanged(lv_obj_t* obj, std::function<void(int)> callback);

// Basic style functions
void _lvSetPos(lv_obj_t* obj, const Position& pos);
void _lvSetSize(lv_obj_t* obj, const Size& size);
void _lvSetWidth(lv_obj_t* obj, int width);
void _lvSetHeight(lv_obj_t* obj, int height);
void _lvSetBgColor(lv_obj_t* obj, lv_color_t color);

// 新的简化样式系统 - 使用统一的 StyleProperty
void _lvSetStyle(lv_obj_t* obj, const StyleProperty& prop);

// State management functions
void _lvAddState(lv_obj_t* obj, lv_state_t state);
void _lvRemoveState(lv_obj_t* obj, lv_state_t state);

} // namespace Gui