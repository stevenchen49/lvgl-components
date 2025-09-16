# LVGL Modern C++ 封装

基于wxUI设计理念的现代化LVGL C++封装，实现声明式UI、延迟构造、生命周期管理、线程安全和响应式编程。

## 🎯 设计目标

1. **声明式编程** - 代码即布局，结构清晰
2. **延迟构造** - 按需创建对象，优化性能
3. **生命周期管理** - 自动内存管理，防止泄漏
4. **线程安全** - 多线程环境下的安全访问
5. **响应式编程** - 数据驱动的UI更新
6. **类型安全** - 编译时错误检查
7. **零成本抽象** - 高级API不牺牲性能

## 🏗️ 核心架构

```
用户API层 (VBox, Button, Label...)
    ↓
抽象接口层 (WidgetBase, Container)
    ↓
概念约束层 (Drawable, Styleable)
    ↓
线程安全层 (ThreadSafeProxy, EventQueue)
    ↓
响应式层 (Observable, DataBinding)
    ↓
LVGL原生层 (lv_obj_t, lv_style_t...)
```

## 🚀 特性预览

### 声明式UI构建
```cpp
using namespace lvgl_modern;

VBox {
    Label { "Hello LVGL!" }
        .fontSize(24)
        .color(Color::Blue),
        
    HBox {
        Button { "OK" }
            .onClick([](){ /* handle */ }),
        Button { "Cancel" }
            .onClick([](){ /* handle */ })
    }.spacing(10),
    
    Slider { 0, 100, 50 }
        .onValueChanged([](int value) {
            std::cout << "Value: " << value << std::endl;
        })
}.padding(20).fitTo(screen);
```

### 响应式数据绑定
```cpp
auto counter = Observable<int>(0);
auto label = Label::create();

// 数据绑定 - 当counter变化时自动更新label
label->bindText(counter.map([](int n) { 
    return "Count: " + std::to_string(n); 
}));

// 触发更新
counter.set(42); // label自动显示 "Count: 42"
```

### 线程安全操作
```cpp
// 从任意线程安全更新UI
std::thread worker([&]() {
    for (int i = 0; i < 100; ++i) {
        // 线程安全的UI更新
        ThreadSafe::post([i, &progressBar]() {
            progressBar->setValue(i);
        });
        std::this_thread::sleep_for(100ms);
    }
});
```

## 📁 项目结构

```
lvgl_modern/
├── include/
│   ├── lvgl_modern/
│   │   ├── core/           # 核心基础设施
│   │   ├── widgets/        # 控件封装
│   │   ├── layouts/        # 布局管理
│   │   ├── reactive/       # 响应式编程
│   │   ├── threading/      # 线程安全
│   │   └── lvgl_modern.hpp # 统一头文件
│   └── mock_lvgl/          # LVGL Mock实现
├── src/                    # 实现文件
├── examples/               # 示例程序
├── tests/                  # 单元测试
└── docs/                   # 文档
```

## 🔧 构建要求

- C++20兼容编译器
- CMake 3.20+
- LVGL 8.3+ (或使用内置Mock)

## 📚 核心概念

### 1. 延迟构造 (Lazy Construction)
对象在声明时创建"蓝图"，在`fitTo()`或`show()`时才实际创建LVGL对象。

### 2. 智能生命周期管理
使用RAII和智能指针自动管理LVGL对象的生命周期。

### 3. 线程安全代理
所有UI操作通过线程安全代理进行，确保多线程环境下的安全性。

### 4. 响应式数据流
通过Observable和数据绑定实现响应式UI更新。

### 5. 类型安全设计
使用C++20 Concepts确保编译时类型安全。
