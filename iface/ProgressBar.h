#pragma once

#include "View.h"
#include "Modifier.h"

namespace Gui {

class ProgressBar : public View, public Modifier<ProgressBar>
{
public:
    ProgressBar(int value = 0) : mValue(value) {}

    ProgressBar& value(int val) & {
        custom([val](lv_obj_t* obj) {
            _lvSetProgressValue(obj, val);
        });
        mValue = val;
        return *this;
    }
    ProgressBar&& value(int val) && {
        return std::move(static_cast<ProgressBar&>(*this).value(val));
    }

    ProgressBar& range(int min, int max) & {
        custom([min, max](lv_obj_t* obj) {
            _lvSetProgressRange(obj, min, max);
        });
        return *this;
    }
    ProgressBar&& range(int min, int max) && {
        return std::move(static_cast<ProgressBar&>(*this).range(min, max));
    }

    ProgressBar& onValueChanged(std::function<void(int)> callback) & {
        custom([callback](lv_obj_t* obj) {
            _lvSetProgressOnValueChanged(obj, callback);
        });
        return *this;
    }
    ProgressBar&& onValueChanged(std::function<void(int)> callback) && {
        return std::move(static_cast<ProgressBar&>(*this).onValueChanged(callback));
    }

    lv_obj_t* _build(lv_obj_t* parent) override {
        mLvObj = _lvCreateProgressBar(parent, mValue);
        if (mLvObj) {
            _applyAllModifiers(mLvObj);
        }
        return mLvObj;
    }

private:
    int mValue;
};

} // namespace Gui
