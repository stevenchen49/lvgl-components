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

    VStack& spacing(int space) & {
        custom([space](lv_obj_t* obj){
            _lvSetStyleGap(obj, space, LV_FLEX_FLOW_COLUMN);
        });
        return *this;
    }
    VStack&& spacing(int space) && {
        return std::move(static_cast<VStack&>(*this).spacing(space));
    }

    VStack& alignment(Layout::Horizontal align) & {
        custom([align](lv_obj_t* obj){
            _lvSetFlexAlignment(obj, align);
        });
        return *this;
    }
    VStack&& alignment(Layout::Horizontal align) && {
        return std::move(static_cast<VStack&>(*this).alignment(align));
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

    HStack& spacing(int space) & {
        custom([space](lv_obj_t* obj){
            _lvSetStyleGap(obj, space, LV_FLEX_FLOW_ROW);
        });
        return *this;
    }
    HStack&& spacing(int space) && {
        return std::move(static_cast<HStack&>(*this).spacing(space));
    }

    HStack& alignment(Layout::Vertical align) & {
        custom([align](lv_obj_t* obj){
            _lvSetFlexAlignment(obj, align);
        });
        return *this;
    }
    HStack&& alignment(Layout::Vertical align) && {
        return std::move(static_cast<HStack&>(*this).alignment(align));
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

class ZStack : public View, public Modifier<ZStack>
{
public:
    ZStack(const std::string& name = "") : View(name) {}

    template <typename... Children>
    ZStack(Children&&... children)
    {
        (addChild(std::forward<Children>(children)), ...);
    }

    template <typename Child>
    ZStack& addChild(Child&& child)
    {
        mChildren.emplace_back(std::make_unique<std::decay_t<Child>>(std::forward<Child>(child)));
        return *this;
    }

    ZStack& add(std::unique_ptr<View> view)
    {
        mChildren.push_back(std::move(view));
        return *this;
    }

public:
    lv_obj_t* _build(lv_obj_t* parent) override
    {
        mLvObj = _lvCreateZStack(parent);
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