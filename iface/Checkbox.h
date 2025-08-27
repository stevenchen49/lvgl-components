#pragma once

#include "View.h"
#include "Modifier.h"
#include <functional>
#include <string>

namespace Gui {

class Checkbox : public View, public Modifier<Checkbox>
{
public:
    using OnToggleCallback = std::function<void(bool)>;

    Checkbox(const std::string& text = "") : View(""), mText(text), mIsChecked(false) {}
    
    Checkbox& text(const std::string& txt) & {
        mText = txt;
        custom([txt](lv_obj_t* obj){
            _lvSetCheckboxText(obj, txt.c_str());
        });
        return *this;
    }
    Checkbox&& text(const std::string& txt) && {
        return std::move(static_cast<Checkbox&>(*this).text(txt));
    }

    Checkbox& isChecked(bool checked) & {
        mIsChecked = checked;
        custom([checked](lv_obj_t* obj){
            _lvSetCheckboxState(obj, checked);
        });
        return *this;
    }
    Checkbox&& isChecked(bool checked) && {
        return std::move(static_cast<Checkbox&>(*this).isChecked(checked));
    }

    Checkbox& onToggle(OnToggleCallback callback) & {
        mOnToggle = std::move(callback);
        return *this;
    }
    Checkbox&& onToggle(OnToggleCallback callback) && {
        return std::move(static_cast<Checkbox&>(*this).onToggle(std::move(callback)));
    }

public:
    lv_obj_t* _build(lv_obj_t* parent) override {
        mLvObj = _lvCreateCheckbox(parent);
        if (mLvObj) {
            if (!mText.empty()) {
                _lvSetCheckboxText(mLvObj, mText.c_str());
            }
            if (mIsChecked) {
                lv_obj_add_state(mLvObj, LV_STATE_CHECKED);
            }
            _applyAllModifiers(mLvObj);
            if (mOnToggle) {
                _lvSetCheckboxOnToggle(mLvObj, mOnToggle);
            }
        }
        return mLvObj;
    }

private:
    std::string mText;
    bool mIsChecked;
    OnToggleCallback mOnToggle;
};

} // namespace Gui
