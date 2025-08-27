#pragma once

#include <string>
#include "lvgl.h"

namespace Gui {

class View 
{
public:
    View(const std::string& name = "") : mName(name) {}
    virtual ~View() = default;

    // This needs to be public to be called from main
    virtual lv_obj_t* _build(lv_obj_t* parent) = 0;

protected:
    lv_obj_t* mLvObj;
    std::string mName;

private:
    lv_obj_t* mLvParent;
};

} // namespace Gui