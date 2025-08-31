#pragma once

#include "Adaptor.h"
#include "ViewBase.h"
#include "Modifier.h"

#include "style/Size.h"
#include "style/Position.h"
#include "style/Color.h"
#include "style/Layout.h"

#include <string>

namespace gui {

template<class Derived>
class View : public ViewBase, public Modifier<Derived>
{
public:
    using Modifier<Derived>::custom;

public:
    View() = default;
    explicit View(std::string name) : ViewBase(std::move(name)) {}

    Derived& backgroundColor(style::Color color) & 
    {
        custom([color](lv_obj_t* obj){ adaptor::_lvSetBgColor(obj, color); });
        return lself();
    }
    Derived&& backgroundColor(style::Color color) && 
    {
        return std::move(static_cast<Derived&>(*this).backgroundColor(color));
    }
    
    Derived& foregroundColor(style::Color color) & 
    {
        custom([color](lv_obj_t* obj){ adaptor::_lvSetTextColor(obj, color); });
        return lself();
    }
    Derived&& foregroundColor(style::Color color) && 
    {
        return std::move(static_cast<Derived&>(*this).foregroundColor(color));
    }

protected:
    using Modifier<Derived>::lself;
    using Modifier<Derived>::rself;
    using Modifier<Derived>::_applyAllModifiers;

protected:
    virtual lv_obj_t* _createLvObj(lv_obj_t* parent) override 
    {
        return adaptor::_lvCreateObj(parent);
    }

    virtual lv_obj_t* _build(lv_obj_t* parent) override 
    {
        if (!mLvObj) {
            mLvObj = _createLvObj(parent);
            if (mLvObj) {
                this->_applyAllModifiers(mLvObj);
            }
        }
        return mLvObj;
    }
};

} // namespace gui