#pragma once

#include "ComponentConfig.h"
#include "ColorConfig.h"
#include <lvgl.h>
#include <memory>
#include <vector>
#include <functional>

namespace Gui {

/**
 * @brief 组件基类
 * 
 * 提供基于 LVGL 的组件封装，支持配置化创建和事件处理
 */
class Component
{
public:
    Component();
    Component(const ComponentConfig& config);
    virtual ~Component();

    // ==================== 创建和初始化 ====================
    
    /**
     * @brief 创建组件对象
     * @param parent 父对象
     * @return LVGL 对象指针
     */
    virtual lv_obj_t* createObject(lv_obj_t* parent) 
    {
        mLvObj = _lvCreateObject(parent);
        if (mLvObj) {
            applyConfig();
        }
        return mLvObj;
    }

    virtual Component& genObjectSync(lv_obj_t* parent = nullptr) 
    {
        if (parent) {
            mParent = parent;
        }
        mLvObj = createObject(mParent);
        return *this;
    }

    /**
     * @brief 应用配置到组件
     */
    virtual void applyConfig();

    // ==================== 配置设置方法 ====================
    
    /**
     * @brief 设置位置
     */
    Component& setPos(const ComponentConfig::Pos& pos)
    {
        mConfig.pos = pos;
        if (mLvObj) {
            _lvSetPos(mLvObj, pos);
        }
        return *this;
    }

    /**
     * @brief 设置布局
     */
    Component& setLayout(const ComponentConfig::Layout& layout)
    {
        mConfig.layout = layout;
        if (mLvObj) {
            _lvSetLayout(mLvObj, layout);
        }
        return *this;
    }

    /**
     * @brief 设置样式
     */
    Component& setStyle(const ComponentConfig::Style& style)
    {
        mConfig.style = style;
        if (mLvObj) {
            _lvSetStyle(mLvObj, style);
        }
        return *this;
    }

    /**
     * @brief 设置文本
     */
    Component& setText(const ComponentConfig::Text& text)
    {
        mConfig.text = text;
        if (mLvObj) {
            _lvSetText(mLvObj, text);
        }
        return *this;
    }

    /**
     * @brief 设置事件
     */
    Component& setEvent(const ComponentConfig::Event& event)
    {
        mConfig.event = event;
        if (mLvObj) {
            _lvSetEvent(mLvObj, event);
        }
        return *this;
    }

    /**
     * @brief 设置动画
     */
    Component& setAnimation(const ComponentConfig::Animation& animation)
    {
        mConfig.animation = animation;
        if (mLvObj) {
            _lvSetAnimation(mLvObj, animation);
        }
        return *this;
    }

    Component& show()
    {
        setVisible(true);
        return *this;
    }
    

    // ==================== 便捷设置方法 ====================
    
    /**
     * @brief 设置位置
     */
    Component& setPos(int32_t x, int32_t y)
    {
        return setPos(ComponentConfig::Pos(x, y));
    }

    /**
     * @brief 设置尺寸
     */
    Component& setSize(int32_t width, int32_t height)
    {
        mConfig.pos.width = width;
        mConfig.pos.height = height;
        if (mLvObj) {
            lv_obj_set_size(mLvObj, width, height);
        }
        return *this;
    }

    /**
     * @brief 设置背景色
     */
    Component& setBgColor(uint32_t color)
    {
        mConfig.style.bgColor = color;
        if (mLvObj) {
            lv_obj_set_style_bg_color(mLvObj, lv_color_hex(color), LV_PART_MAIN);
        }
        return *this;
    }

    /**
     * @brief 设置文本色
     */
    Component& setTextColor(uint32_t color)
    {
        mConfig.style.textColor = color;
        if (mLvObj) {
            lv_obj_set_style_text_color(mLvObj, lv_color_hex(color), LV_PART_MAIN);
        }
        return *this;
    }

    /**
     * @brief 设置文本内容
     */
    Component& setText(const std::string& text)
    {
        mConfig.text.content = text;
        mConfig.text.enabled = true;
        if (mLvObj) {
            // 注意：lv_obj_set_text 可能不存在，需要根据具体对象类型设置文本
            // 这里暂时注释掉，由具体的子类实现
            // lv_obj_set_text(mLvObj, text.c_str());
        }
        return *this;
    }

    /**
     * @brief 设置点击事件
     */
    Component& setOnClick(std::function<void(lv_event_t*)> callback)
    {
        mConfig.event.onClick = callback;
        if (mLvObj && callback) {
            lv_obj_add_event_cb(mLvObj, _onClickCallback, LV_EVENT_CLICKED, this);
        }
        return *this;
    }

    /**
     * @brief 设置可见性
     */
    Component& setVisible(bool visible)
    {
        mConfig.visible = visible;
        if (mLvObj) {
            if (visible) {
                lv_obj_clear_flag(mLvObj, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_add_flag(mLvObj, LV_OBJ_FLAG_HIDDEN);
            }
        }
        return *this;
    }

    /**
     * @brief 设置启用状态
     */
    Component& setEnabled(bool enabled)
    {
        mConfig.enabled = enabled;
        if (mLvObj) {
            if (enabled) {
                lv_obj_clear_state(mLvObj, LV_STATE_DISABLED);
            } else {
                lv_obj_add_state(mLvObj, LV_STATE_DISABLED);
            }
        }
        return *this;
    }

    // ==================== 获取方法 ====================
    
    /**
     * @brief 获取 LVGL 对象
     */
    lv_obj_t* getLvObj() const { return mLvObj; }
    
    /**
     * @brief 获取配置
     */
    const ComponentConfig& getConfig() const { return mConfig; }
    
    /**
     * @brief 获取组件ID
     */
    const std::string& getId() const { return mConfig.id; }

    // ==================== 子组件管理 ====================
    
    /**
     * @brief 添加子组件
     */
    void addChild(std::shared_ptr<Component> child)
    {
        if (child && mLvObj) {
            child->createObject(mLvObj);
            mChildren.push_back(child);
        }
    }

    /**
     * @brief 移除子组件
     */
    void removeChild(std::shared_ptr<Component> child)
    {
        auto it = std::find(mChildren.begin(), mChildren.end(), child);
        if (it != mChildren.end()) {
            mChildren.erase(it);
        }
    }

    /**
     * @brief 获取子组件列表
     */
    const std::vector<std::shared_ptr<Component>>& getChildren() const
    {
        return mChildren;
    }

protected:
    // ==================== 静态 LVGL 操作方法 ====================
    
    /**
     * @brief 创建 LVGL 对象
     */
    static lv_obj_t* _lvCreateObject(lv_obj_t* parent);

    /**
     * @brief 设置位置
     */
    static lv_obj_t* _lvSetPos(lv_obj_t* obj, const ComponentConfig::Pos& pos);

    /**
     * @brief 设置布局
     */
    static lv_obj_t* _lvSetLayout(lv_obj_t* obj, const ComponentConfig::Layout& layout);

    /**
     * @brief 设置样式
     */
    static lv_obj_t* _lvSetStyle(lv_obj_t* obj, const ComponentConfig::Style& style);

    /**
     * @brief 设置文本
     */
    static lv_obj_t* _lvSetText(lv_obj_t* obj, const ComponentConfig::Text& text);

    static void _lvSetVisable(lv_obj_t* obj, bool visible);
    static void _lvSetEnabled(lv_obj_t* obj, bool enabled);

    /**
     * @brief 设置事件
     */
    static lv_obj_t* _lvSetEvent(lv_obj_t* obj, const ComponentConfig::Event& event);

    /**
     * @brief 设置动画
     */
    static lv_obj_t* _lvSetAnimation(lv_obj_t* obj, const ComponentConfig::Animation& animation);

    // ==================== 事件回调 ====================
    
    /**
     * @brief 点击事件回调
     */
    static void _onClickCallback(lv_event_t* e);

    /**
     * @brief 长按事件回调
     */
    static void _onLongPressCallback(lv_event_t* e);

    /**
     * @brief 焦点事件回调
     */
    static void _onFocusCallback(lv_event_t* e);

    /**
     * @brief 失焦事件回调
     */
    static void _onBlurCallback(lv_event_t* e);

protected:
    lv_obj_t* mParent = nullptr;                                    ///< 父对象
    lv_obj_t* mLvObj = nullptr;                                     ///< LVGL 对象
    ComponentConfig mConfig;                                         ///< 组件配置
    std::vector<std::shared_ptr<Component>> mChildren;              ///< 子组件列表
};

} // namespace Gui