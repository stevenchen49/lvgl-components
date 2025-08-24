#pragma once

#include "Component.h"
#include <lvgl.h>

namespace Gui {

// 前向声明
struct SwitchConfig;

/**
 * @brief 开关组件
 * 
 * 提供开关功能，支持开启/关闭状态切换
 */
class Switch : public Component {
public:
    // ==================== 构造函数/析构函数 ====================
    
    /**
     * @brief 默认构造函数
     */
    Switch();
    
    /**
     * @brief 带配置构造函数
     * @param config 开关配置
     */
    Switch(const SwitchConfig& config);
    
    /**
     * @brief 析构函数
     */
    virtual ~Switch();
    
    // ==================== 核心方法 ====================
    
    /**
     * @brief 创建 LVGL 对象
     * @param parent 父对象
     * @return LVGL 对象指针
     */
    lv_obj_t* createObject(lv_obj_t* parent) override;
    
    /**
     * @brief 生成对象并同步
     * @param parent 父对象，nullptr 表示使用活动屏幕
     * @return 自身引用，支持链式调用
     */
    Switch& genObjectSync(lv_obj_t* parent = nullptr) override;
    
    // ==================== 开关特有方法 ====================
    
    /**
     * @brief 设置开关配置
     * @param config 开关配置
     * @return 自身引用，支持链式调用
     */
    Switch& setConfig(const SwitchConfig& config);
    
    /**
     * @brief 设置开启状态
     * @param on 是否开启
     * @return 自身引用，支持链式调用
     */
    Switch& setOn(bool on);
    
    /**
     * @brief 获取开启状态
     * @return 是否开启
     */
    bool isOn() const;
    
    /**
     * @brief 切换开关状态
     * @return 自身引用，支持链式调用
     */
    Switch& toggle();
    
protected:
    // ==================== 静态辅助方法 ====================
    
    /**
     * @brief 创建 LVGL 开关对象
     * @param parent 父对象
     * @return LVGL 对象指针
     */
    static lv_obj_t* _lvCreateSwitch(lv_obj_t* parent);
    
    /**
     * @brief 设置 LVGL 开关配置
     * @param obj LVGL 对象
     * @param config 开关配置
     */
    static void _lvSetConfig(lv_obj_t* obj, const SwitchConfig& config);
    
private:
    bool mOn = false;   ///< 开关状态
};

} // namespace Gui
