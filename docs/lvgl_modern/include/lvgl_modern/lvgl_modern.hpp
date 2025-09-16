#pragma once
// LVGL Modern - 统一头文件

// 核心模块
#include "core/concepts.hpp"
#include "core/widget_base.hpp"

// 线程安全模块
#include "threading/thread_safe.hpp"

// 响应式编程模块
#include "reactive/observable.hpp"

// 控件模块
#include "widgets/label.hpp"
#include "widgets/button.hpp"
#include "widgets/slider.hpp"

// 布局模块
#include "layouts/containers.hpp"

// Mock LVGL
#include <mock_lvgl/lvgl.h>

namespace lvgl_modern {

// 导入常用类型到主命名空间
using namespace widgets;
using namespace layouts;
using namespace reactive;
using namespace threading;

// 颜色常量
namespace Color {
    constexpr lv_color_t White = LV_COLOR_WHITE;
    constexpr lv_color_t Black = LV_COLOR_BLACK;
    constexpr lv_color_t Red = LV_COLOR_RED;
    constexpr lv_color_t Green = LV_COLOR_GREEN;
    constexpr lv_color_t Blue = LV_COLOR_BLUE;
}

// 应用程序类 - 管理整个应用生命周期
class Application {
public:
    Application() {
        // 初始化线程安全系统
        ThreadSafe::initialize();
        std::cout << "[Application] LVGL Modern initialized" << std::endl;
    }
    
    ~Application() {
        ThreadSafe::shutdown();
        std::cout << "[Application] LVGL Modern shutdown" << std::endl;
    }
    
    // 获取屏幕对象
    lv_obj_t* screen() const {
        return lv_scr_act();
    }
    
    // 运行主循环
    void run() {
        std::cout << "[Application] Starting main loop" << std::endl;
        
        // 模拟主循环
        for (int i = 0; i < 10; ++i) {
            // 处理线程安全任务队列
            ThreadSafe::processTasks();
            
            // 模拟LVGL任务处理
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        
        std::cout << "[Application] Main loop finished" << std::endl;
    }
    
    // 禁止拷贝和移动
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;
    Application(Application&&) = delete;
    Application& operator=(Application&&) = delete;
    
private:
    ThreadGuard thread_guard_;
};

// 全局应用实例
inline Application& app() {
    static Application instance;
    return instance;
}

// 便利的屏幕访问函数
inline lv_obj_t* screen() {
    return app().screen();
}

} // namespace lvgl_modern
