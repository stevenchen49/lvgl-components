#pragma once

#include "../View.h"

#include <string>
#include <functional>

namespace gui {

class Button : public View<Button>
{
public:
    using OnClickCallback = std::function<void()>;

public:
    Button() : View<Button>() {}
    explicit Button(const std::string& text) : View<Button>(), mText(text) {}

    ViewType type() const override { return ViewType::Button; }
    
    Button& text(const std::string& text) &
    {
        mText = text;
        custom([text](lv_obj_t* obj){ adaptor::_lvSetButtonText(obj, text.c_str()); });
        return *this;
    }

    Button&& text(const std::string& text) &&
    {
        return std::move(static_cast<Button&>(*this).text(text));
    }

    Button& onClick(OnClickCallback callback)
    {
        mOnClick = std::move(callback);
        return *this;
    }

protected:
    lv_obj_t* _createLvObj(lv_obj_t* parent) override
    {
        return adaptor::_lvCreateButton(parent);
    }

    lv_obj_t* _build(lv_obj_t* parent) override
    {
        mLvObj = _createLvObj(parent);
        if (mLvObj) {
            if (!mText.empty()) {
                adaptor::_lvSetButtonText(mLvObj, mText.c_str());
            }
            this->_applyAllModifiers(mLvObj);
            if (mOnClick) {
                adaptor::_lvSetOnClick(mLvObj, mOnClick);
            }
        }
        return mLvObj;
    }

private:
    std::string mText;
    OnClickCallback mOnClick;
};

} // namespace gui