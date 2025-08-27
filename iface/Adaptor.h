#pragma once

#include "lvgl.h"
#include "Style.h"
#include <functional>

namespace Gui {

// Forward declarations for LVGL implementation functions
lv_obj_t* _lvCreateVStack(lv_obj_t* parent);
lv_obj_t* _lvCreateHStack(lv_obj_t* parent);

lv_obj_t* _lvCreateLabel(lv_obj_t* parent);
void _lvSetText(lv_obj_t* obj, const char* text);

lv_obj_t* _lvCreateButton(lv_obj_t* parent, const char* text);
void _lvSetOnClick(lv_obj_t* obj, std::function<void()> callback);

void _lvSetSize(lv_obj_t* obj, const Gui::Size& size);
void _lvSetWidth(lv_obj_t* obj, int width);
void _lvSetHeight(lv_obj_t* obj, int height);
void _lvSetBgColor(lv_obj_t* obj, lv_color_t color);

} // namespace Gui