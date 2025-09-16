// LVGL Modern 线程安全示例 - 展示多线程UI更新

#include <lvgl_modern/lvgl_modern.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <random>

using namespace lvgl_modern;

int main() {
    std::cout << "\n=== LVGL Modern Threading Example ===" << std::endl;
    
    // 创建响应式数据
    auto progress = makeProperty<int>(0);
    auto status = makeProperty<std::string>("Ready");
    auto workerCount = makeProperty<int>(0);
    
    // 创建控件代理
    Label::Proxy statusLabel;
    Label::Proxy progressLabel;
    Label::Proxy workerLabel;
    Slider::Proxy progressBar;
    Button::Proxy startBtn;
    Button::Proxy stopBtn;
    
    std::cout << "\n--- Creating Thread-Safe UI ---" << std::endl;
    
    // 声明式UI构建
    VBox {
        Label { "Multi-Threading Demo" }
            .fontSize(20)
            .color(Color::Green),
            
        Label { "Status: Ready" }
            .withProxy(statusLabel)
            .bindText(status.map([](const std::string& s) { 
                return "Status: " + s; 
            })),
            
        Label { "Progress: 0%" }
            .withProxy(progressLabel)
            .bindText(progress.map([](int p) { 
                return "Progress: " + std::to_string(p) + "%"; 
            })),
            
        Slider { 0, 100, 0 }
            .withProxy(progressBar)
            .bindValue(progress),
            
        Label { "Active Workers: 0" }
            .withProxy(workerLabel)
            .bindText(workerCount.map([](int count) { 
                return "Active Workers: " + std::to_string(count); 
            })),
            
        HBox {
            Button { "Start Workers" }
                .withProxy(startBtn)
                .onClick([&]() {
                    std::cout << "[Event] Starting worker threads..." << std::endl;
                    status = "Working";
                    progress = 0;
                    
                    // 启动多个工作线程
                    static std::vector<std::thread> workers;
                    workers.clear();
                    
                    for (int i = 0; i < 3; ++i) {
                        workers.emplace_back([&, i]() {
                            // 线程安全地增加工作线程计数
                            ThreadSafe::post([&]() {
                                workerCount = workerCount.get() + 1;
                            });
                            
                            std::random_device rd;
                            std::mt19937 gen(rd());
                            std::uniform_int_distribution<> dis(100, 500);
                            
                            for (int step = 0; step < 10; ++step) {
                                // 模拟工作
                                std::this_thread::sleep_for(std::chrono::milliseconds(dis(gen)));
                                
                                // 线程安全地更新UI
                                ThreadSafe::post([&, i, step]() {
                                    int current_progress = progress.get();
                                    progress = std::min(100, current_progress + 3);
                                    
                                    std::cout << "[Worker " << i << "] Progress update: " 
                                              << progress.get() << "%" << std::endl;
                                    
                                    if (progress.get() >= 100) {
                                        status = "Completed";
                                    }
                                });
                            }
                            
                            // 线程安全地减少工作线程计数
                            ThreadSafe::post([&]() {
                                workerCount = workerCount.get() - 1;
                                std::cout << "[Worker] Thread finished" << std::endl;
                            });
                        });
                    }
                    
                    // 分离线程让它们在后台运行
                    for (auto& worker : workers) {
                        worker.detach();
                    }
                }),
                
            Button { "Reset" }
                .withProxy(stopBtn)
                .onClick([&]() {
                    std::cout << "[Event] Resetting..." << std::endl;
                    
                    // 线程安全地重置状态
                    ThreadSafe::post([&]() {
                        status = "Ready";
                        progress = 0;
                        workerCount = 0;
                    });
                })
        }.spacing(10).center()
        
    }.padding(20).fitTo(screen());
    
    std::cout << "\n--- UI Created Successfully ---" << std::endl;
    
    // 演示线程安全操作
    std::cout << "\n--- Demonstrating Thread Safety ---" << std::endl;
    
    // 模拟外部线程更新UI
    std::thread externalUpdater([&]() {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        
        std::cout << "\n[External Thread] Starting external updates..." << std::endl;
        
        for (int i = 0; i < 5; ++i) {
            // 从外部线程安全地更新UI
            ThreadSafe::post([&, i]() {
                status = "External Update " + std::to_string(i + 1);
                std::cout << "[External Thread] Status updated: " << status.get() << std::endl;
            });
            
            std::this_thread::sleep_for(std::chrono::milliseconds(800));
        }
        
        // 触发工作线程启动
        ThreadSafe::post([&]() {
            startBtn->simulateClick();
        });
        
        std::cout << "\n[External Thread] External updates completed" << std::endl;
    });
    
    // 运行应用主循环
    std::cout << "\n--- Running Main Loop ---" << std::endl;
    
    // 扩展主循环以处理更多任务
    for (int i = 0; i < 50; ++i) {
        ThreadSafe::processTasks();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        
        // 每隔一段时间显示状态
        if (i % 10 == 0) {
            std::cout << "[Main Loop] Iteration " << i 
                      << ", Progress: " << progress.get() 
                      << "%, Workers: " << workerCount.get() << std::endl;
        }
    }
    
    // 等待外部线程完成
    externalUpdater.join();
    
    std::cout << "\n--- Final State ---" << std::endl;
    std::cout << "Status: " << status.get() << std::endl;
    std::cout << "Progress: " << progress.get() << "%" << std::endl;
    std::cout << "Workers: " << workerCount.get() << std::endl;
    
    std::cout << "\n=== Threading Example Completed ===" << std::endl;
    return 0;
}
