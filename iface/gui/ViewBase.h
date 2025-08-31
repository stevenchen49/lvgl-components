#pragma once

#include "Adaptor.h"

#include <string>
#include <memory>
#include <atomic>

namespace gui {

enum class ViewType {
    VStack,
    HStack,
    ZStack,
    Label,
    Button
};

class ViewBase 
{
public:
    ViewBase() = default;
    explicit ViewBase(std::string name) : mName(std::move(name)) {}

    virtual ~ViewBase() 
    {
        if (mDestroyedPtr) {
            mDestroyedPtr->store(true, std::memory_order_release);
            _destroy();
        }
    }

    ViewBase(const ViewBase&) = delete;
    ViewBase& operator=(const ViewBase&) = delete;

    ViewBase(ViewBase&& o) noexcept
        : mDestroyedPtr(std::move(o.mDestroyedPtr))
        , mName(std::move(o.mName))
        , mLvParent(o.mLvParent)
        , mLvObj(o.mLvObj) 
    {
        o.mLvParent = nullptr; 
        o.mLvObj = nullptr;
        o.mIsWrapper = false;
    }

    ViewBase& operator=(ViewBase&& o) noexcept 
    {
        if (this == &o) {
            return *this;
        }

        if (mDestroyedPtr) {
            mDestroyedPtr->store(true, std::memory_order_release);
            _destroy();
        }
        
        mDestroyedPtr = std::move(o.mDestroyedPtr);
        mName = std::move(o.mName);
        mLvParent = o.mLvParent;
        mLvObj = o.mLvObj;
      
        if (o.mDestroyedPtr) {
            o.mDestroyedPtr->store(true, std::memory_order_release);
        }
        o.mLvParent = nullptr; 
        o.mLvObj = nullptr;
        o.mIsWrapper = false;
        
        return *this;
    }

    virtual ViewType type() const = 0;

    void renderSafe(std::function<void()> task);
    
    /**
     * @brief Create and build the view with given parent
     * @param[in] parent Parent LVGL object
     * @return Created LVGL object
     */
    lv_obj_t* create(lv_obj_t* parent) 
    {
        return _build(parent);
    }
    
    lv_obj_t* _getLvParent() const { return mLvParent; }
    lv_obj_t* _getLvObj() const { return mLvObj; }

protected:
    virtual lv_obj_t* _createLvObj(lv_obj_t* parent) = 0;
    virtual lv_obj_t* _build(lv_obj_t* parent) = 0;

    void _destroy(); 
    
protected:
    std::shared_ptr<std::atomic<bool>> mDestroyedPtr;
    lv_obj_t* mLvParent = nullptr;
    lv_obj_t* mLvObj = nullptr;
    bool mIsWrapper = false;
    std::string mName;
};

} // namespace gui