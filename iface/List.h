#pragma once

#include "View.h"
#include "Modifier.h"
#include <vector>
#include <string>

namespace Gui {

class List : public View, public Modifier<List>
{
public:
    List() = default;

    template <typename... Items>
    List(Items&&... items) {
        (addItem(std::forward<Items>(items)), ...);
    }

    List& addItem(const std::string& text) & {
        mItems.push_back(text);
        return *this;
    }
    List&& addItem(const std::string& text) && {
        return std::move(static_cast<List&>(*this).addItem(text));
    }

    List& onItemSelected(std::function<void(int index, const std::string&)> callback) & {
        custom([callback](lv_obj_t* obj) {
            _lvSetListOnItemSelected(obj, callback);
        });
        return *this;
    }
    List&& onItemSelected(std::function<void(int index, const std::string&)> callback) && {
        return std::move(static_cast<List&>(*this).onItemSelected(callback));
    }

    lv_obj_t* _build(lv_obj_t* parent) override {
        mLvObj = _lvCreateList(parent);
        if (mLvObj) {
            _applyAllModifiers(mLvObj);
            for (const auto& item : mItems) {
                _lvAddListItem(mLvObj, item.c_str());
            }
        }
        return mLvObj;
    }

private:
    std::vector<std::string> mItems;
};

} // namespace Gui
