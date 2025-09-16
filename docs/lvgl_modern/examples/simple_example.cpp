// LVGL Modern 简化示例 - 展示核心功能

#include <lvgl_modern/lvgl_modern.hpp>
#include <iostream>
#include <thread>
#include <chrono>

using namespace lvgl_modern;

int main() {
    std::cout << "\n=== LVGL Modern Simple Example ===" << std::endl;
    
    // 创建响应式数据
    auto counter = makeProperty<int>(0);
    auto message = makeProperty<std::string>("Hello LVGL Modern!");
    
    std::cout << "\n--- Creating Individual Widgets ---" << std::endl;
    
    // 创建单个控件并测试 - 避免拷贝构造
    Label titleLabel("LVGL Modern Demo");
    titleLabel.fontSize(24).color(Color::Blue);
    
    Label counterLabel("Counter: 0");
    
    Button incrementBtn("Increment");
    incrementBtn.onClick([&counter]() {
        counter = counter.get() + 1;
        std::cout << "[Event] Counter incremented to: " << counter.get() << std::endl;
    });
    
    Slider valueSlider(0, 100, 50);
    valueSlider.onValueChanged([](int value) {
        std::cout << "[Event] Slider value changed to: " << value << std::endl;
    });
    
    std::cout << "\n--- Creating Widgets on Screen ---" << std::endl;
    
    // 直接在屏幕上创建控件
    titleLabel.createAndAdd(screen());
    counterLabel.createAndAdd(screen());
    incrementBtn.createAndAdd(screen());
    valueSlider.createAndAdd(screen());
    
    std::cout << "\n--- Testing Responsive Programming ---" << std::endl;
    
    // 测试响应式编程
    counter.subscribe([](int value) {
        std::cout << "[Reactive] Counter changed to: " << value << std::endl;
    });
    
    message.subscribe([](const std::string& msg) {
        std::cout << "[Reactive] Message changed to: " << msg << std::endl;
    });
    
    std::cout << "\n--- Testing Thread Safety ---" << std::endl;
    
    // 测试线程安全
    std::thread worker([&]() {
        for (int i = 1; i <= 5; ++i) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            
            // 从工作线程安全地更新UI
            ThreadSafe::post([&, i]() {
                counter = i * 10;
                message = "Update from thread: " + std::to_string(i);
            });
        }
        
        std::cout << "[Worker] Thread completed" << std::endl;
    });
    
    std::cout << "\n--- Running Main Loop ---" << std::endl;
    
    // 运行主循环处理线程安全任务
    for (int i = 0; i < 30; ++i) {
        ThreadSafe::processTasks();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        
        if (i % 10 == 0) {
            std::cout << "[Main Loop] Processing tasks... iteration " << i << std::endl;
        }
    }
    
    // 等待工作线程完成
    worker.join();
    
    std::cout << "\n--- Testing Widget Interactions ---" << std::endl;
    
    // 模拟用户交互
    incrementBtn.simulateClick();
    incrementBtn.simulateClick();
    valueSlider.simulateValueChange(75);
    
    std::cout << "\n--- Final State ---" << std::endl;
    std::cout << "Counter: " << counter.get() << std::endl;
    std::cout << "Message: " << message.get() << std::endl;
    std::cout << "Slider: " << valueSlider.getValue() << std::endl;
    
    std::cout << "\n--- Testing Observable Operations ---" << std::endl;
    
    // 测试Observable的函数式操作
    auto doubledCounter = counter.map([](int n) { return n * 2; });
    auto filteredCounter = counter.filter([](int n) { return n > 50; });
    
    doubledCounter.subscribe([](int value) {
        std::cout << "[Mapped] Doubled counter: " << value << std::endl;
    });
    
    filteredCounter.subscribe([](int value) {
        std::cout << "[Filtered] Counter > 50: " << value << std::endl;
    });
    
    // 触发更新
    counter = 25;  // 不会触发过滤器
    counter = 60;  // 会触发过滤器
    
    // 处理剩余的任务
    ThreadSafe::processTasks();
    
    std::cout << "\n=== Simple Example Completed ===" << std::endl;
    return 0;
}