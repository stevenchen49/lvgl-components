#include "Component.h"

namespace Gui {

Component::Component() : mParent(nullptr), mLvObj(nullptr)
{
}

Component::Component(const ComponentConfig& config) 
    : mParent(nullptr), mLvObj(nullptr), mConfig(config)
{
}

Component::~Component()
{
    // 清理子组件
    mChildren.clear();
    
    // 注意：不在这里删除 mLvObj，因为 LVGL 会管理对象生命周期
    // 或者由父组件管理
}

void Component::applyConfig()
{
    if (!mLvObj) return;

    // 应用位置配置
    _lvSetPos(mLvObj, mConfig.pos);
    
    // 应用布局配置
    _lvSetLayout(mLvObj, mConfig.layout);
    
    // 应用样式配置
    _lvSetStyle(mLvObj, mConfig.style);
    
    // 应用文本配置
    _lvSetText(mLvObj, mConfig.text);
    
    // 应用事件配置
    _lvSetEvent(mLvObj, mConfig.event);
    
    // 应用动画配置
    _lvSetAnimation(mLvObj, mConfig.animation);
    
    // 应用可见性
    setVisible(mConfig.visible);
    
    // 应用启用状态
    setEnabled(mConfig.enabled);
    
    // 应用可点击性
    if (mConfig.clickable) {
        lv_obj_add_flag(mLvObj, LV_OBJ_FLAG_CLICKABLE);
    } else {
        lv_obj_clear_flag(mLvObj, LV_OBJ_FLAG_CLICKABLE);
    }
    
    // 应用可获得焦点性
    if (mConfig.focusable) {
        lv_obj_add_flag(mLvObj, LV_OBJ_FLAG_CLICKABLE);
        // 注意：LVGL 中可点击的对象通常也可以获得焦点
    }
}

// ==================== 静态 LVGL 操作方法实现 ====================

lv_obj_t* Component::_lvCreateObject(lv_obj_t* parent)
{
    // 默认创建一个基础对象，子类可以重写
    return lv_obj_create(parent);
}

lv_obj_t* Component::_lvSetPos(lv_obj_t* obj, const ComponentConfig::Pos& pos)
{
    if (!obj) return nullptr;
    
    lv_obj_set_pos(obj, pos.x, pos.y);
    return obj;
}

lv_obj_t* Component::_lvSetLayout(lv_obj_t* obj, const ComponentConfig::Layout& layout)
{
    if (!obj) return nullptr;
    
    // 设置弹性布局
    lv_obj_set_layout(obj, LV_LAYOUT_FLEX);
    lv_obj_set_style_flex_flow(obj, layout.flexFlow, 0);
    lv_obj_set_style_flex_main_place(obj, layout.mainPlace, 0);
    lv_obj_set_style_flex_cross_place(obj, layout.crossPlace, 0);
    lv_obj_set_style_flex_track_place(obj, layout.trackPlace, 0);
    // 注意：rowGap 和 columnGap 可能需要使用不同的 API
    
    return obj;
}

lv_obj_t* Component::_lvSetStyle(lv_obj_t* obj, const ComponentConfig::Style& style)
{
    if (!obj) return nullptr;
    
    // 设置背景颜色
    if (style.bgColor != 0) {
        lv_obj_set_style_bg_color(obj, lv_color_hex(style.bgColor), LV_PART_MAIN);
        lv_obj_set_style_bg_opa(obj, style.bgOpacity, LV_PART_MAIN);
    }
    
    // 设置文本颜色
    if (style.textColor != 0) {
        lv_obj_set_style_text_color(obj, lv_color_hex(style.textColor), LV_PART_MAIN);
        lv_obj_set_style_text_opa(obj, style.textOpacity, LV_PART_MAIN);
    }
    
    // 设置边框
    if (style.borderWidth > 0) {
        lv_obj_set_style_border_width(obj, style.borderWidth, LV_PART_MAIN);
        if (style.borderColor != 0) {
            lv_obj_set_style_border_color(obj, lv_color_hex(style.borderColor), LV_PART_MAIN);
            lv_obj_set_style_border_opa(obj, style.borderOpacity, LV_PART_MAIN);
        }
    }
    
    // 设置圆角
    if (style.radius > 0) {
        lv_obj_set_style_radius(obj, style.radius, LV_PART_MAIN);
    }
    
    // 设置内边距和外边距
    if (style.padding > 0) {
        lv_obj_set_style_pad_all(obj, style.padding, LV_PART_MAIN);
    }
    if (style.margin > 0) {
        lv_obj_set_style_margin_all(obj, style.margin, LV_PART_MAIN);
    }
    
    return obj;
}

lv_obj_t* Component::_lvSetText(lv_obj_t* obj, const ComponentConfig::Text& text)
{
    if (!obj) return nullptr;
    
    // 注意：这个方法需要根据具体的对象类型来实现
    // 对于按钮，可能需要获取标签对象
    // 这里暂时不实现，由子类重写
    
    return obj;
}

lv_obj_t* Component::_lvSetEvent(lv_obj_t* obj, const ComponentConfig::Event& event)
{
    if (!obj) return nullptr;
    
    // 事件设置暂时不实现，由子类重写
    return obj;
}

lv_obj_t* Component::_lvSetAnimation(lv_obj_t* obj, const ComponentConfig::Animation& animation)
{
    if (!obj) return nullptr;
    
    // 动画设置暂时不实现，由子类重写
    return obj;
}

// ==================== 事件回调实现 ====================

void Component::_onClickCallback(lv_event_t* e)
{
    // 点击事件回调暂时不实现
}

void Component::_onLongPressCallback(lv_event_t* e)
{
    // 长按事件回调暂时不实现
}

void Component::_onFocusCallback(lv_event_t* e)
{
    // 焦点事件回调暂时不实现
}

void Component::_onBlurCallback(lv_event_t* e)
{
    // 失焦事件回调暂时不实现
}

} // namespace Gui
