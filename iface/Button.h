#pragma once

#include "Component.h"
#include "ButtonConfig.h"

namespace Gui {

/**
 * @brief Button component
 */
class Button : public Component
{
public:
    Button();
    virtual ~Button();

    /**
     * @brief Create button object
     * @param parent Parent LVGL object
     * @return Created LVGL button object
     */
    lv_obj_t* createObject(lv_obj_t* parent) override;

    Button& genObjectSync(lv_obj_t* parent = nullptr) override
    {
        Component::genObjectSync(parent);
        return *this;
    }

    Button& setConfig(const ButtonConfig& config)
    {
        _lvSetConfig(mLvObj, config);
        return *this;
    }

protected:
    // ==================== 静态辅助方法 ====================
    static lv_obj_t* _lvCreateButton(lv_obj_t* parent);
    static void _lvSetConfig(lv_obj_t* obj, const ButtonConfig& config);

private:
    // ==================== 私有成员变量 ====================
    std::string mButtonText;        ///< Button text
};

} // namespace Gui