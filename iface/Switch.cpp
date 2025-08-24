#include "Switch.h"
#include "SwitchConfig.h"

namespace Gui {

// ==================== 构造函数/析构函数 ====================

Switch::Switch() : Component()
{
}

Switch::Switch(const SwitchConfig& config) : Component(), mOn(config.isOn)
{
}

Switch::~Switch()
{
}

// ==================== 核心方法 ====================

lv_obj_t* Switch::createObject(lv_obj_t* parent)
{
    return _lvCreateSwitch(parent);
}

Switch& Switch::genObjectSync(lv_obj_t* parent)
{
    Component::genObjectSync(parent);
    return *this;
}

// ==================== 开关特有方法 ====================

Switch& Switch::setConfig(const SwitchConfig& config)
{
    _lvSetConfig(mLvObj, config);
    mOn = config.isOn;
    return *this;
}

Switch& Switch::setOn(bool on)
{
    mOn = on;
    if (mLvObj) {
        lv_obj_add_state(mLvObj, on ? LV_STATE_CHECKED : 0);
    }
    return *this;
}

bool Switch::isOn() const
{
    return mOn;
}

Switch& Switch::toggle()
{
    return setOn(!mOn);
}

} // namespace Gui
