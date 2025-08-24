#pragma once

#include "Component.h"
#include "RadioConfig.h"

namespace Gui {

/**
 * @brief Radio component
 * 
 * LVGL radio button component wrapper
 */
class Radio : public Component
{
public:
    // ==================== 构造函数/析构函数 ====================
    Radio();
    Radio(const RadioConfig& config);
    virtual ~Radio();

    // ==================== 核心方法 ====================
    /**
     * @brief Create radio object
     * @param parent Parent LVGL object
     * @return Created LVGL radio object
     */
    lv_obj_t* createObject(lv_obj_t* parent) override;

    Radio& genObjectSync(lv_obj_t* parent = nullptr) override
    {
        Component::genObjectSync(parent);
        return *this;
    }

    Radio& setConfig(const RadioConfig& config)
    {
        _lvSetConfig(mLvObj, config);
        return *this;
    }

    // ==================== 单选按钮特有方法 ====================
    /**
     * @brief Set radio checked state
     * @param checked Checked state
     * @return Reference to this object for chaining
     */
    Radio& setChecked(bool checked);

    /**
     * @brief Get radio checked state
     * @return Current checked state
     */
    bool isChecked() const;

protected:
    // ==================== 静态辅助方法 ====================
    static lv_obj_t* _lvCreateRadio(lv_obj_t* parent);
    static void _lvSetConfig(lv_obj_t* obj, const RadioConfig& config);

private:
    // ==================== 私有成员变量 ====================
    bool mChecked = false;           ///< Radio checked state
};

} // namespace Gui
