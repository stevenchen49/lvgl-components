#pragma once

#include "ComponentConfig.h"
#include "ColorConfig.h"

#include <memory>
#include <vector>
#include <functional>
#include <lvgl.h>

namespace Gui {

/**
 * @brief 组件基类
 * 
 * 提供基于 LVGL 的组件封装，支持配置化创建和事件处理
 */
class Component
{
public:
    Component() : mParent(nullptr), mLvObj(nullptr) {}
    
    virtual ~Component() {}
 
    lv_obj_t* getLvObj() const { return mLvObj; }
    
    virtual lv_obj_t* createObject(lv_obj_t* parent) 
    {
        mLvObj = _lvCreateObject(parent);
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

    Component& setPos(const ComponentConfig::Pos& pos)
    {
        _lvSetPos(mLvObj, pos);
        return *this;
    }

    Component& setLayout(const ComponentConfig::Layout& layout)
    {
        _lvSetLayout(mLvObj, layout);
        return *this;
    }
 
    Component& setVisible(bool visible)
    {
        _lvSetVisable(mLvObj, visible);
        return *this;
    }

    Component& setEnabled(bool enabled)
    {
        _lvSetEnabled(mLvObj, enabled);
        return *this;
    }
  
    Component& show()
    {
        setVisible(true);
        return *this;
    }
 
protected:
    // ==================== 静态 LVGL 操作方法 ====================
 
    static lv_obj_t* _lvCreateObject(lv_obj_t* parent);
    static void _lvSetPos(lv_obj_t* obj, const ComponentConfig::Pos& pos);
    static void _lvSetLayout(lv_obj_t* obj, const ComponentConfig::Layout& layout);
    static void _lvSetVisable(lv_obj_t* obj, bool visible);
    static void _lvSetEnabled(lv_obj_t* obj, bool enabled);
    
protected:
    lv_obj_t* mParent = nullptr;                                    
    lv_obj_t* mLvObj = nullptr;                                     
};

} // namespace Gui