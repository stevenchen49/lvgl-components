#pragma once

#include "style/Size.h"
#include "style/Layout.h"
#include "style/Color.h"

#include <functional>

struct _lv_obj_t;
typedef _lv_obj_t lv_obj_t;

namespace gui {
namespace adaptor {

int _lvPreinit();
int _lvInit();
void _lvDeinit();
void _lvLoop();
void _lvAsyncCall(std::function<void()> task);

// Forward declarations for LVGL implementation functions
lv_obj_t* _lvCreateObj(lv_obj_t* parent);
void _lvDestroyObj(lv_obj_t* obj);

lv_obj_t* _lvCreateVStack(lv_obj_t* parent);
lv_obj_t* _lvCreateHStack(lv_obj_t* parent);
lv_obj_t* _lvCreateZStack(lv_obj_t* parent);

void _lvSetFlexAlignment(lv_obj_t* obj, style::Layout::Horizontal align);
void _lvSetFlexAlignment(lv_obj_t* obj, style::Layout::Vertical align);

lv_obj_t* _lvCreateLabel(lv_obj_t* parent);
void _lvSetText(lv_obj_t* obj, const char* text);

lv_obj_t* _lvCreateButton(lv_obj_t* parent);
void _lvSetButtonText(lv_obj_t* obj, const char* text);
void _lvSetOnClick(lv_obj_t* obj, std::function<void()> callback);

void _lvSetBgColor(lv_obj_t* obj, const style::Color& color);
void _lvSetTextColor(lv_obj_t* obj, const style::Color& color);

} // namespace adaptor
} // namespace gui