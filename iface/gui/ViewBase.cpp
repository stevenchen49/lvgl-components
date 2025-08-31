#include "ViewBase.h"
#include "Render.h"

namespace gui {

void ViewBase::renderSafe(std::function<void()> task) 
{
    std::weak_ptr<std::atomic<bool>> destroyed = mDestroyedPtr;
     
    Render::instance().post(nullptr, [destroyed, task = std::move(task)](lv_obj_t*) {
        if (auto sp = destroyed.lock()) {
            if (!sp->load(std::memory_order_acquire)) {
                task();
            }
        }
    });
}

lv_obj_t* ViewBase::_createLvObj(lv_obj_t* parent)
{
    mLvObj = adaptor::_lvCreateObj(parent);
    return mLvObj;
}

void ViewBase::_destroy() 
{
    if (mLvObj && !mIsWrapper) {
        auto* doomed = mLvObj;
        mLvObj = nullptr;
        Render::instance().post(doomed, [](lv_obj_t* o){ 
            adaptor::_lvDestroyObj(o); 
        });
    }
}

} // namespace gui