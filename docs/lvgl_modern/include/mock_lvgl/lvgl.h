#pragma once
// Mock LVGL API for development and testing

#include <cstdint>
#include <string>
#include <iostream>
#include <functional>
#include <vector>
#include <memory>

// 基本类型定义
using lv_coord_t = int16_t;
using lv_color_t = uint32_t;
using lv_opa_t = uint8_t;

// 对象类型
struct lv_obj_t {
    static inline int next_id = 1;
    int id;
    lv_obj_t* parent = nullptr;
    std::vector<std::unique_ptr<lv_obj_t>> children;
    std::string type_name;
    
    lv_obj_t(const std::string& type = "obj") : id(next_id++), type_name(type) {
        std::cout << "[LVGL] Created " << type << " object (ID: " << id << ")" << std::endl;
    }
    
    virtual ~lv_obj_t() {
        std::cout << "[LVGL] Destroyed " << type_name << " object (ID: " << id << ")" << std::endl;
    }
};

// 样式类型
struct lv_style_t {
    int id;
    static inline int next_id = 1;
    
    lv_style_t() : id(next_id++) {
        std::cout << "[LVGL] Created style (ID: " << id << ")" << std::endl;
    }
    
    ~lv_style_t() {
        std::cout << "[LVGL] Destroyed style (ID: " << id << ")" << std::endl;
    }
};

// 事件类型
enum lv_event_code_t {
    LV_EVENT_CLICKED,
    LV_EVENT_VALUE_CHANGED,
    LV_EVENT_FOCUSED,
    LV_EVENT_DEFOCUSED
};

struct lv_event_t {
    lv_obj_t* target;
    lv_event_code_t code;
    void* user_data;
};

using lv_event_cb_t = std::function<void(lv_event_t*)>;

// 布局类型
enum lv_flex_flow_t {
    LV_FLEX_FLOW_ROW,
    LV_FLEX_FLOW_COLUMN,
    LV_FLEX_FLOW_ROW_WRAP,
    LV_FLEX_FLOW_COLUMN_WRAP
};

// 对齐方式
enum lv_flex_align_t {
    LV_FLEX_ALIGN_START,
    LV_FLEX_ALIGN_END,
    LV_FLEX_ALIGN_CENTER,
    LV_FLEX_ALIGN_SPACE_EVENLY,
    LV_FLEX_ALIGN_SPACE_AROUND,
    LV_FLEX_ALIGN_SPACE_BETWEEN
};

// 颜色常量
constexpr lv_color_t LV_COLOR_WHITE = 0xFFFFFF;
constexpr lv_color_t LV_COLOR_BLACK = 0x000000;
constexpr lv_color_t LV_COLOR_RED = 0xFF0000;
constexpr lv_color_t LV_COLOR_GREEN = 0x00FF00;
constexpr lv_color_t LV_COLOR_BLUE = 0x0000FF;

// Mock API函数
inline lv_obj_t* lv_obj_create(lv_obj_t* parent) {
    auto obj = std::make_unique<lv_obj_t>("obj");
    auto* ptr = obj.get();
    if (parent) {
        obj->parent = parent;
        parent->children.push_back(std::move(obj));
        std::cout << "[LVGL] Added child to parent (ID: " << parent->id << ")" << std::endl;
    }
    return ptr;
}

inline lv_obj_t* lv_label_create(lv_obj_t* parent) {
    auto obj = std::make_unique<lv_obj_t>("label");
    auto* ptr = obj.get();
    if (parent) {
        obj->parent = parent;
        parent->children.push_back(std::move(obj));
    }
    return ptr;
}

inline lv_obj_t* lv_btn_create(lv_obj_t* parent) {
    auto obj = std::make_unique<lv_obj_t>("button");
    auto* ptr = obj.get();
    if (parent) {
        obj->parent = parent;
        parent->children.push_back(std::move(obj));
    }
    return ptr;
}

inline lv_obj_t* lv_slider_create(lv_obj_t* parent) {
    auto obj = std::make_unique<lv_obj_t>("slider");
    auto* ptr = obj.get();
    if (parent) {
        obj->parent = parent;
        parent->children.push_back(std::move(obj));
    }
    return ptr;
}

inline void lv_label_set_text(lv_obj_t* label, const char* text) {
    std::cout << "[LVGL] Label (ID: " << label->id << ") text set to: '" << text << "'" << std::endl;
}

inline void lv_obj_add_event_cb(lv_obj_t* obj, lv_event_cb_t cb, lv_event_code_t filter, void* user_data) {
    std::cout << "[LVGL] Event callback added to object (ID: " << obj->id << ") for event: " << filter << std::endl;
    (void)cb; (void)user_data; // 避免未使用警告
}

inline void lv_obj_set_size(lv_obj_t* obj, lv_coord_t w, lv_coord_t h) {
    std::cout << "[LVGL] Object (ID: " << obj->id << ") size set to: " << w << "x" << h << std::endl;
}

inline void lv_obj_set_pos(lv_obj_t* obj, lv_coord_t x, lv_coord_t y) {
    std::cout << "[LVGL] Object (ID: " << obj->id << ") position set to: (" << x << ", " << y << ")" << std::endl;
}

inline void lv_obj_set_flex_flow(lv_obj_t* obj, lv_flex_flow_t flow) {
    std::cout << "[LVGL] Object (ID: " << obj->id << ") flex flow set to: " << flow << std::endl;
}

inline void lv_obj_set_flex_align(lv_obj_t* obj, lv_flex_align_t main_place, lv_flex_align_t cross_place, lv_flex_align_t track_place) {
    std::cout << "[LVGL] Object (ID: " << obj->id << ") flex align set" << std::endl;
    (void)main_place; (void)cross_place; (void)track_place;
}

inline void lv_slider_set_range(lv_obj_t* slider, int32_t min, int32_t max) {
    std::cout << "[LVGL] Slider (ID: " << slider->id << ") range set to: [" << min << ", " << max << "]" << std::endl;
}

inline void lv_slider_set_value(lv_obj_t* slider, int32_t value, bool anim) {
    std::cout << "[LVGL] Slider (ID: " << slider->id << ") value set to: " << value << (anim ? " (animated)" : "") << std::endl;
}

inline int32_t lv_slider_get_value(const lv_obj_t* slider) {
    std::cout << "[LVGL] Getting slider (ID: " << slider->id << ") value" << std::endl;
    return 50; // Mock value
}

// 全局屏幕对象
inline lv_obj_t* lv_scr_act() {
    static auto screen = std::make_unique<lv_obj_t>("screen");
    return screen.get();
}
