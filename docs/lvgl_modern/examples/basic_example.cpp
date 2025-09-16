// LVGL Modern 基础示例 - 展示声明式UI和响应式编程

#include <lvgl_modern/lvgl_modern.hpp>
#include <iostream>
#include <thread>
#include <chrono>

using namespace lvgl_modern;

int main() {
    std::cout << "\n=== LVGL Modern Basic Example ===" << std::endl;
    
    // 创建响应式数据
    auto counter = makeProperty<int>(0);
    auto isEnabled = makeProperty<bool>(true);
    
    // 创建控件代理
    Label::Proxy counterLabel;
    Button::Proxy incrementBtn;
    Button::Proxy decrementBtn;
    Slider::Proxy valueSlider;
    
    std::cout << "\n--- Creating Declarative UI ---" << std::endl;
    
    // 声明式UI构建 - 使用移动语义
    auto layout = VBox();
    layout.add(Label("LVGL Modern Demo")
        .fontSize(24)
        .color(Color::Blue));
    
    layout.add(Label("Counter: 0")
        .withProxy(counterLabel)
        .bindText(counter.map([](int n) { 
            return "Counter: " + std::to_string(n); 
        })));
    
    auto hbox1 = HBox();
    hbox1.add(Button("Increment")
        .withProxy(incrementBtn)
        .onClick([&counter]() {
            counter = counter.get() + 1;
            std::cout << "[Event] Counter incremented to: " << counter.get() << std::endl;
        }));
    
    hbox1.add(Button("Decrement")
        .withProxy(decrementBtn)
        .onClick([&counter]() {
            counter = counter.get() - 1;
            std::cout << "[Event] Counter decremented to: " << counter.get() << std::endl;
        })
        .bindEnabled(isEnabled));
    
    layout.add(std::move(hbox1).spacing(10));
    
    layout.add(Slider(0, 100, 50)
        .withProxy(valueSlider)
        .onValueChanged([&](int value) {
            std::cout << "[Event] Slider value changed to: " << value << std::endl;
            // 当滑块值小于25时禁用减少按钮
            isEnabled = value >= 25;
        }));
    
    auto hbox2 = HBox();
    hbox2.add(Button("Reset")
        .onClick([&counter, &valueSlider]() {
            counter = 0;
            valueSlider->simulateValueChange(50);
            std::cout << "[Event] Reset clicked" << std::endl;
        }));
    
    hbox2.add(Button("Exit")
        .onClick([]() {
            std::cout << "[Event] Exit clicked" << std::endl;
        }));
    
    layout.add(std::move(hbox2).spacing(10).center());
    
    std::move(layout).padding(20).fitTo(screen());
    
    std::cout << "\n--- UI Created Successfully ---" << std::endl;
    
    // 演示响应式编程
    std::cout << "\n--- Demonstrating Reactive Programming ---" << std::endl;
    
    // 模拟用户交互
    std::thread userSimulation([&]() {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        
        // 模拟按钮点击
        std::cout << "\n[Simulation] Simulating increment button clicks..." << std::endl;
        for (int i = 0; i < 5; ++i) {
            incrementBtn->simulateClick();
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
        
        // 模拟滑块操作
        std::cout << "\n[Simulation] Simulating slider changes..." << std::endl;
        valueSlider->simulateValueChange(20); // 这会禁用减少按钮
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        
        decrementBtn->simulateClick(); // 这应该不会生效，因为按钮被禁用
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        
        valueSlider->simulateValueChange(80); // 重新启用减少按钮
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        
        decrementBtn->simulateClick(); // 现在应该生效
        
        std::cout << "\n[Simulation] User simulation completed" << std::endl;
    });
    
    // 运行应用主循环
    app().run();
    
    // 等待模拟线程完成
    userSimulation.join();
    
    std::cout << "\n--- Final State ---" << std::endl;
    std::cout << "Counter: " << counter.get() << std::endl;
    std::cout << "Slider: " << valueSlider->getValue() << std::endl;
    std::cout << "Decrement enabled: " << isEnabled.get() << std::endl;
    
    std::cout << "\n=== Example Completed ===" << std::endl;
    return 0;
}