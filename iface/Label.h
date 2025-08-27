#pragma once

#include "View.h"

namespace Gui {

class Label : public View, public Modifier<Label>
{
public:
    Label(const std::string& text) : View(""), mText(text) {}

protected:
    lv_obj_t* _build(lv_obj_t* parent) override 
    {
        mLvObj = _lvCreateLabel(parent);
        if (mLvObj) {
            _lvSetText(mLvObj, mText.c_str());
            _applyAllModifiers(mLvObj);
        }
        return mLvObj;
    }

private:
    std::string mText;
};

} // namespace Gui