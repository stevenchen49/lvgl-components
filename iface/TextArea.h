#pragma once

#include "View.h"
#include "Modifier.h"
#include <string>

namespace Gui {

class TextArea : public View, public Modifier<TextArea>
{
public:
    TextArea(const std::string& placeholder = "") : mPlaceholder(placeholder) {}

    TextArea& text(const std::string& text) & {
        custom([text](lv_obj_t* obj) {
            _lvSetTextAreaText(obj, text.c_str());
        });
        return *this;
    }
    TextArea&& text(const std::string& text) && {
        return std::move(static_cast<TextArea&>(*this).text(text));
    }

    TextArea& placeholder(const std::string& placeholder) & {
        custom([placeholder](lv_obj_t* obj) {
            _lvSetTextAreaPlaceholder(obj, placeholder.c_str());
        });
        return *this;
    }
    TextArea&& placeholder(const std::string& placeholder) && {
        return std::move(static_cast<TextArea&>(*this).placeholder(placeholder));
    }

    TextArea& onTextChanged(std::function<void(const std::string&)> callback) & {
        custom([callback](lv_obj_t* obj) {
            _lvSetTextAreaOnTextChanged(obj, callback);
        });
        return *this;
    }
    TextArea&& onTextChanged(std::function<void(const std::string&)> callback) && {
        return std::move(static_cast<TextArea&>(*this).onTextChanged(callback));
    }

    TextArea& maxLength(uint32_t max_len) & {
        custom([max_len](lv_obj_t* obj) {
            _lvSetTextAreaMaxLength(obj, max_len);
        });
        return *this;
    }
    TextArea&& maxLength(uint32_t max_len) && {
        return std::move(static_cast<TextArea&>(*this).maxLength(max_len));
    }

    lv_obj_t* _build(lv_obj_t* parent) override {
        mLvObj = _lvCreateTextArea(parent);
        if (mLvObj) {
            if (!mPlaceholder.empty()) {
                _lvSetTextAreaPlaceholder(mLvObj, mPlaceholder);
            }
            _applyAllModifiers(mLvObj);
        }
        return mLvObj;
    }

private:
    std::string mPlaceholder;
};

} // namespace Gui
