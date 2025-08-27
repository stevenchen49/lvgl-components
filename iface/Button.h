#pragma once

#include "View.h"
#include "Modifier.h"
#include <string>
#include <functional>

namespace Gui {

class Button : public View, public Modifier<Button>
{
public:
    using OnClickCallback = std::function<void()>;

    Button(const std::string& text) : View(""), mText(text) {}

    Button& onClick(OnClickCallback callback)
    {
        mOnClick = std::move(callback);
        return *this;
    }

protected:
    lv_obj_t* _build(lv_obj_t* parent) override
    {
        mLvObj = _lvCreateButton(parent);
        if (mLvObj) {
            _lvSetText(mLvObj, mText);
            _applyAllModifiers(mLvObj);
            if (mOnClick) {
                // The actual event registration will be handled by the backend implementation
                _lvSetOnClick(mLvObj, mOnClick);
            }
        }
        return mLvObj;
    }

private:
    std::string mText;
    OnClickCallback mOnClick;
};

} // namespace Gui