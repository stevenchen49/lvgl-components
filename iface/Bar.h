#pragma once

#include "View.h"
#include "Modifier.h"

namespace Gui {

class Bar : public View, public Modifier<Bar>
{
public:
    Bar(int value = 0) : mValue(value) {}

    Bar& value(int val) & {
        custom([val](lv_obj_t* obj) {
            _lvSetBarValue(obj, val);
        });
        mValue = val;
        return *this;
    }
    Bar&& value(int val) && {
        return std::move(static_cast<Bar&>(*this).value(val));
    }

    Bar& range(int min, int max) & {
        custom([min, max](lv_obj_t* obj) {
            _lvSetBarRange(obj, min, max);
        });
        return *this;
    }
    Bar&& range(int min, int max) && {
        return std::move(static_cast<Bar&>(*this).range(min, max));
    }

    Bar& onValueChanged(std::function<void(int)> callback) & {
        custom([callback](lv_obj_t* obj) {
            _lvSetBarOnValueChanged(obj, callback);
        });
        return *this;
    }
    Bar&& onValueChanged(std::function<void(int)> callback) && {
        return std::move(static_cast<Bar&>(*this).onValueChanged(callback));
    }

    lv_obj_t* _build(lv_obj_t* parent) override {
        mLvObj = _lvCreateBar(parent, mValue);
        if (mLvObj) {
            _applyAllModifiers(mLvObj);
        }
        return mLvObj;
    }

private:
    int mValue;
};

} // namespace Gui
