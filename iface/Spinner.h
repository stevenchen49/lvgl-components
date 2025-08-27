#pragma once

#include "View.h"
#include "Modifier.h"

namespace Gui {

class Spinner : public View, public Modifier<Spinner>
{
public:
    Spinner() = default;

    Spinner& time(uint32_t time) & {
        custom([time](lv_obj_t* obj) {
            _lvSetSpinnerTime(obj, time);
        });
        return *this;
    }
    Spinner&& time(uint32_t time) && {
        return std::move(static_cast<Spinner&>(*this).time(time));
    }

    Spinner& angle(uint16_t angle) & {
        custom([angle](lv_obj_t* obj) {
            _lvSetSpinnerAngle(obj, angle);
        });
        return *this;
    }
    Spinner&& angle(uint16_t angle) && {
        return std::move(static_cast<Spinner&>(*this).angle(angle));
    }

    lv_obj_t* _build(lv_obj_t* parent) override {
        mLvObj = _lvCreateSpinner(parent);
        if (mLvObj) {
            _applyAllModifiers(mLvObj);
        }
        return mLvObj;
    }
};

} // namespace Gui
