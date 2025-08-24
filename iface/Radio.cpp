#include "Radio.h"

namespace Gui {

// ==================== 构造函数/析构函数 ====================

Radio::Radio() : Component()
{
}

Radio::Radio(const RadioConfig& config) : Component(), mChecked(config.isChecked)
{
}

Radio::~Radio()
{
}

// ==================== 核心方法 ====================

lv_obj_t* Radio::createObject(lv_obj_t* parent)
{
    return _lvCreateRadio(parent);
}

// ==================== 单选按钮特有方法 ====================

Radio& Radio::setChecked(bool checked)
{
    mChecked = checked;
    if (mLvObj) {
        if (checked) {
            lv_obj_add_state(mLvObj, LV_STATE_CHECKED);
        } else {
            lv_obj_remove_state(mLvObj, LV_STATE_CHECKED);
        }
    }
    return *this;
}

bool Radio::isChecked() const
{
    return mChecked;
}

} // namespace Gui
