#pragma once

#include "../View.h"

#include <vector>
#include <memory>
#include <type_traits>

namespace gui {

template<class Derived>
class Container : public View<Derived>
{
public:
    using View<Derived>::lself;
    using View<Derived>::rself;

public:
    Container() = default;
    explicit Container(std::string name) : View<Derived>(std::move(name)) {}

    virtual ViewType type() const override = 0;
    
    template<class... Children>
    explicit Container(Children&&... cs) 
    {
        (addChild(std::forward<Children>(cs)), ...);
    }

    template<class Child,
             class T = std::decay_t<Child>,
             std::enable_if_t<std::is_base_of_v<ViewBase, T>, int> = 0>
    Derived& addChild(Child&& child) & 
    {
        mChildren.emplace_back(std::make_unique<T>(std::forward<Child>(child)));
        return lself();
    }  
    
    template<class Child,
             class T = std::decay_t<Child>,
             std::enable_if_t<std::is_base_of_v<ViewBase, T>, int> = 0>
    Derived&& addChild(Child&& child) && 
    {
        mChildren.emplace_back(std::make_unique<T>(std::forward<Child>(child)));
        return rself();
    }

protected:
    virtual lv_obj_t* _createLvObj(lv_obj_t* parent) override
    {
        return adaptor::_lvCreateObj(parent);
    }

    virtual lv_obj_t* _build(lv_obj_t* parent) override 
    {
        mLvObj = _createLvObj(parent);
        if (mLvObj) {
            _applyAllModifiers(mLvObj);
            for (auto& child : mChildren) {
                child->_build(mLvObj);
            }
        }
        return mLvObj;
    }

protected:
    std::vector<std::unique_ptr<ViewBase>> mChildren;
};

class VStack : public Container<VStack>
{
public:
    using Container<VStack>::addChild;

public:
    VStack(const std::string& name = "") : Container<VStack>(name) {}

    template <typename... Children>
    VStack(Children&&... children)
        : Container<VStack>(std::forward<Children>(children)...) {}
     
    ViewType type() const override { return ViewType::VStack; }
    
    VStack& spacing(int space) & 
    {
        mSpacing = space;
        return lself();
    }
    VStack&& spacing(int space) && 
    {
        return std::move(static_cast<VStack&>(*this).spacing(space));
    }

    VStack& alignment(style::Layout::Horizontal align) & 
    {
        mHorizontalAlign = align;
        return lself();
    }
    
    VStack&& alignment(style::Layout::Horizontal align) && 
    {
        return std::move(static_cast<VStack&>(*this).alignment(align));
    }

protected:
    lv_obj_t* _createLvObj(lv_obj_t* parent) override
    {
        return adaptor::_lvCreateVStack(parent);
    }

    lv_obj_t* _build(lv_obj_t* parent) override
    {
        mLvObj = _createLvObj(parent);
        if (mLvObj) {
            if (mSpacing > 0) {
                // adaptor::_lvSetStyleGap(mLvObj, mSpacing, LV_FLEX_FLOW_COLUMN);
            }
            if (mHorizontalAlign != style::Layout::Horizontal::Leading) {
                // adaptor::_lvSetFlexAlignment(mLvObj, mHorizontalAlign);
            }
            this->_applyAllModifiers(mLvObj);
            for (auto& child : mChildren) {
                child->_build(mLvObj);
            }
        }
        return mLvObj;
    }

private:
    int mSpacing = 0;
    style::Layout::Horizontal mHorizontalAlign = style::Layout::Horizontal::Leading;
};  

class HStack : public Container<HStack>
{
public:
    using Container<HStack>::addChild;

public:
    HStack(const std::string& name = "") : Container<HStack>(name) {}

    template <typename... Children>
    HStack(Children&&... children)
        : Container<HStack>(std::forward<Children>(children)...) {}
    
    ViewType type() const override { return ViewType::HStack; }
    
    HStack& spacing(int space) & 
    {
        mSpacing = space;
        return lself();
    }
    HStack&& spacing(int space) && 
    {
        return std::move(static_cast<HStack&>(*this).spacing(space));
    }

    HStack& alignment(style::Layout::Horizontal align) & 
    {
        mHorizontalAlign = align;
        return lself();
    } 
    HStack&& alignment(style::Layout::Horizontal align) && 
    {
        return std::move(static_cast<HStack&>(*this).alignment(align));
    }

protected:
    lv_obj_t* _createLvObj(lv_obj_t* parent) override
    {
        return adaptor::_lvCreateHStack(parent);
    }

    lv_obj_t* _build(lv_obj_t* parent) override
    {
        mLvObj = _createLvObj(parent);
        if (mLvObj) {
            if (mSpacing > 0) {
                // adaptor::_lvSetStyleGap(mLvObj, mSpacing, LV_FLEX_FLOW_ROW);
            }
            if (mHorizontalAlign != style::Layout::Horizontal::Leading) {
                // adaptor::_lvSetFlexAlignment(mLvObj, mHorizontalAlign);
            }
            this->_applyAllModifiers(mLvObj);
            for (auto& child : mChildren) {
                child->_build(mLvObj);
            }
        }
        return mLvObj;
    }

private:
    int mSpacing = 0;
    style::Layout::Horizontal mHorizontalAlign = style::Layout::Horizontal::Leading;
};

class ZStack : public Container<ZStack>
{
public:
    using Container<ZStack>::addChild;

public:
    ZStack(const std::string& name = "") : Container<ZStack>(name) {}

    template <typename... Children>
    ZStack(Children&&... children)
        : Container<ZStack>(std::forward<Children>(children)...) {}

    ViewType type() const override { return ViewType::ZStack; }

protected:
    lv_obj_t* _createLvObj(lv_obj_t* parent) override
    {
        return adaptor::_lvCreateZStack(parent);
    }    
};

} // namespace gui