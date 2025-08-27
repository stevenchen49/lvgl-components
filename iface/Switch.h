#pragma once

#include "View.h"
#include "Modifier.h"
#include <functional>

namespace Gui {

class Switch : public View, public Modifier<Switch>
{
public:
    using OnToggleCallback = std::function<void(bool)>;

    Switch(bool initialIsOn = false) : View(""), mIsOn(initialIsOn) {}
    
    Switch& isOn(bool on) & {
        mIsOn = on;
        custom([on](lv_obj_t* obj){
            _lvSetSwitchState(obj, on);
        });
        return *this;
    }
    Switch&& isOn(bool on) && {
        return std::move(static_cast<Switch&>(*this).isOn(on));
    }

    Switch& onToggle(OnToggleCallback callback) & {
        mOnToggle = std::move(callback);
        return *this;
    }
    Switch&& onToggle(OnToggleCallback callback) && {
        return std::move(static_cast<Switch&>(*this).onToggle(std::move(callback)));
    }

public:
    lv_obj_t* _build(lv_obj_t* parent) override {
        mLvObj = _lvCreateSwitch(parent);
        if (mLvObj) {
            if (mIsOn) {
                lv_obj_add_state(mLvObj, LV_STATE_CHECKED);
            } else {
                lv_obj_clear_state(mLvObj, LV_STATE_CHECKED);
            }
            _applyAllModifiers(mLvObj);
            if (mOnToggle) {
                _lvSetSwitchOnToggle(mLvObj, mOnToggle);
            }
        }
        return mLvObj;
    }

private:
    bool mIsOn;
    OnToggleCallback mOnToggle;
};

} // namespace Gui
