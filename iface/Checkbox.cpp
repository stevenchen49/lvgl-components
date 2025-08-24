#include "Checkbox.h"

namespace Gui {

// ==================== 构造函数/析构函数 ====================

Checkbox::Checkbox() : Component()
{
}

Checkbox::Checkbox(const CheckboxConfig& config) : Component(), mChecked(config.isChecked)
{
}

Checkbox::~Checkbox()
{
}

// ==================== 核心方法 ====================

lv_obj_t* Checkbox::createObject(lv_obj_t* parent)
{
    return _lvCreateCheckbox(parent);
}

// ==================== 复选框特有方法 ====================

Checkbox& Checkbox::setChecked(bool checked)
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

bool Checkbox::isChecked() const
{
    return mChecked;
}

} // namespace Gui
