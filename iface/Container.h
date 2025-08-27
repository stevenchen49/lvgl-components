#pragma once

#include "View.h"

namespace Gui {

class VStack : public View, public Modifier<VStack>
{
public:
    VStack(const std::string& name = "") : View(name) {}

    template <typename... Children>
    VStack(Children&&... children)
    {
        (addChild(std::forward<Children>(children)), ...);
    }

    template <typename Child>
    VStack& addChild(Child&& child)
    {
        mChildren.emplace_back(std::make_unique<std::decay_t<Child>>(std::forward<Child>(child)));
        return *this;
    }

    VStack& add(std::unique_ptr<View> view)
    {
        mChildren.push_back(std::move(view));
        return *this;
    }

    lv_obj_t* _build(lv_obj_t* parent) override
    {
        mLvObj = _lvCreateVStack(parent);
        if (mLvObj) {
            _applyAllModifiers(mLvObj);
            for (auto& child : mChildren) {
                child->_build(mLvObj);
            }
        }
        return mLvObj;
    }

private:
    std::vector<std::unique_ptr<View>> mChildren;
};  

class HStack : public View, public Modifier<HStack>
{
public:
    HStack(const std::string& name = "") : View(name) {}

    template <typename... Children>
    HStack(Children&&... children)
    {
        (addChild(std::forward<Children>(children)), ...);
    }

    template <typename Child>
    HStack& addChild(Child&& child)
    {
        mChildren.emplace_back(std::make_unique<std::decay_t<Child>>(std::forward<Child>(child)));
        return *this;
    }

    HStack& add(std::unique_ptr<View> view)
    {
        mChildren.push_back(std::move(view));
        return *this;
    }

    lv_obj_t* _build(lv_obj_t* parent) override
    {
        mLvObj = _lvCreateHStack(parent);
        if (mLvObj) {
            _applyAllModifiers(mLvObj);
            for (auto& child : mChildren) {
                child->_build(mLvObj);
            }
        }
        return mLvObj;
    }

private:
    std::vector<std::unique_ptr<View>> mChildren;
};

} // namespace Gui