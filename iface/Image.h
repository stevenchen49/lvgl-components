#pragma once

#include "View.h"
#include "Modifier.h"

namespace Gui {

class Image : public View, public Modifier<Image>
{
public:
    Image(const lv_img_dsc_t* src = nullptr) : View(""), mSrc(src) {}

    Image& src(const lv_img_dsc_t* image_src) & {
        mSrc = image_src;
        custom([image_src](lv_obj_t* obj){
            _lvSetImageSrc(obj, image_src);
        });
        return *this;
    }
    Image&& src(const lv_img_dsc_t* image_src) && {
        return std::move(static_cast<Image&>(*this).src(image_src));
    }

public:
    lv_obj_t* _build(lv_obj_t* parent) override {
        mLvObj = _lvCreateImage(parent);
        if (mLvObj) {
            if (mSrc) {
                _lvSetImageSrc(mLvObj, mSrc);
            }
            _applyAllModifiers(mLvObj);
        }
        return mLvObj;
    }

private:
    const lv_img_dsc_t* mSrc;
};

} // namespace Gui
