#pragma once

#include "Component.h"
#include "CheckboxConfig.h"

namespace Gui {

/**
 * @brief Checkbox component
 * 
 * LVGL checkbox component wrapper
 */
class Checkbox : public Component
{
public:
    // ==================== 构造函数/析构函数 ====================
    Checkbox();
    Checkbox(const CheckboxConfig& config);
    virtual ~Checkbox();

    // ==================== 核心方法 ====================
    /**
     * @brief Create checkbox object
     * @param parent Parent LVGL object
     * @return Created LVGL checkbox object
     */
    lv_obj_t* createObject(lv_obj_t* parent) override;

    Checkbox& genObjectSync(lv_obj_t* parent = nullptr) override
    {
        Component::genObjectSync(parent);
        return *this;
    }

    Checkbox& setConfig(const CheckboxConfig& config)
    {
        _lvSetConfig(mLvObj, config);
        return *this;
    }

    // ==================== 复选框特有方法 ====================
    /**
     * @brief Set checkbox checked state
     * @param checked Checked state
     * @return Reference to this object for chaining
     */
    Checkbox& setChecked(bool checked);

    /**
     * @brief Get checkbox checked state
     * @return Current checked state
     */
    bool isChecked() const;

protected:
    // ==================== 静态辅助方法 ====================
    static lv_obj_t* _lvCreateCheckbox(lv_obj_t* parent);
    static void _lvSetConfig(lv_obj_t* obj, const CheckboxConfig& config);

private:
    // ==================== 私有成员变量 ====================
    bool mChecked = false;           ///< Checkbox checked state
};

} // namespace Gui
