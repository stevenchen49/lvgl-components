#pragma once

#include "View.h"
#include "Modifier.h"
#include <functional>

namespace Gui {

class Slider : public View, public Modifier<Slider>
{
public:
    using OnValueChangedCallback = std::function<void(int)>;

    Slider(int initialValue = 0) : View(""), mValue(initialValue) {}

    Slider& range(int min, int max) & {
        custom([min, max](lv_obj_t* obj){
            _lvSetSliderRange(obj, min, max);
        });
        return *this;
    }
    Slider&& range(int min, int max) && {
        return std::move(static_cast<Slider&>(*this).range(min, max));
    }

    Slider& value(int val) & {
        mValue = val; // Store it for build time
        custom([val](lv_obj_t* obj){
            _lvSetSliderValue(obj, val, true); // with animation
        });
        return *this;
    }
    Slider&& value(int val) && {
        return std::move(static_cast<Slider&>(*this).value(val));
    }
    
    Slider& onValueChanged(OnValueChangedCallback callback) & {
        mOnValueChanged = std::move(callback);
        return *this;
    }
    Slider&& onValueChanged(OnValueChangedCallback callback) && {
        return std::move(static_cast<Slider&>(*this).onValueChanged(std::move(callback)));
    }

public:
    lv_obj_t* _build(lv_obj_t* parent) override {
        mLvObj = _lvCreateSlider(parent);
        if (mLvObj) {
            _lvSetSliderValue(mLvObj, mValue, false); // no animation at creation
            _applyAllModifiers(mLvObj);
            if (mOnValueChanged) {
                _lvSetSliderOnValueChanged(mLvObj, mOnValueChanged);
            }
        }
        return mLvObj;
    }

private:
    int mValue;
    OnValueChangedCallback mOnValueChanged;
};

} // namespace Gui
