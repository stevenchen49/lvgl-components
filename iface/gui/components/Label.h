#pragma once

#include "../View.h"

#include <string>

namespace gui {

class Label : public View<Label>
{
public:
    Label() : View<Label>() {}
    explicit Label(std::string text) : View<Label>(), mText(std::move(text)) {}

    Label& text(std::string text) &
    {
        mText = text;
        custom([text](lv_obj_t* obj){ adaptor::_lvSetText(obj, text.c_str()); });
        return lself();
    }
    Label&& text(std::string text) &&
    {
        return std::move(static_cast<Label&>(*this).text(std::move(text)));
    }

    ViewType type() const override { return ViewType::Label; }

protected:
    virtual lv_obj_t* _createLvObj(lv_obj_t* parent) override
    {
        return adaptor::_lvCreateLabel(parent);
    }

    virtual lv_obj_t* _build(lv_obj_t* parent) override
    {
        mLvObj = _createLvObj(parent);
        if (mLvObj) {
            if (!mText.empty()) {
                adaptor::_lvSetText(mLvObj, mText.c_str());
            }
            this->_applyAllModifiers(mLvObj);
        }
        return mLvObj;
    }

private:
    std::string mText;
};

} // namespace gui