# wxUI Mock Explorer

这是一个深度探索wxUI实现原理的项目，通过Mock实现替换了wxWidgets的原生层，使用日志打印来展示wxUI的工作机制。

## 项目目标

1. **理解wxUI架构**：通过Mock实现深入理解wxUI的设计模式和实现原理
2. **学习现代C++技术**：展示CRTP、Type Erasure、Concepts等现代C++技术的应用
3. **可视化工作流程**：通过日志输出清晰地展示UI构建和事件处理过程
4. **教学和调试工具**：为学习wxUI提供一个无GUI依赖的环境

## 项目结构

```
explore/
├── CMakeLists.txt          # 构建配置
├── build.sh               # 构建脚本
├── README.md              # 项目说明
├── include/               # Mock头文件
│   ├── wx/               # Mock wxWidgets
│   │   ├── wx.h          # 基础类型和常量
│   │   ├── window.h      # 窗口基类
│   │   ├── sizer.h       # 布局管理器
│   │   ├── app.h         # 应用程序框架
│   │   ├── button.h      # 按钮控件
│   │   ├── stattext.h    # 静态文本控件
│   │   ├── textctrl.h    # 文本输入控件
│   │   └── checkbox.h    # 复选框控件
│   └── wxUI_mock/        # Mock扩展
└── src/                  # 源代码
    ├── main.cpp          # 主程序入口
    ├── MockWidgets.cpp   # Mock控件实现
    └── ExplorerApp.cpp   # 探索应用程序
```

## 核心特性

### 1. Mock wxWidgets实现
- **完整的类层次结构**：模拟了wxWidgets的主要类
- **事件系统**：实现了事件绑定和触发机制
- **日志输出**：所有操作都有详细的日志记录
- **类型兼容**：与真实wxWidgets API保持兼容

### 2. wxUI核心机制展示
- **声明式UI构建**：展示VSizer/HSizer的工作原理
- **CRTP模式**：演示WidgetDetails的继承机制
- **Proxy系统**：展示运行时对象访问机制
- **事件绑定**：演示类型擦除的事件处理
- **ForEach构造**：展示动态UI生成

### 3. 深度分析功能
- **构建过程可视化**：详细的日志显示UI构建步骤
- **内存管理追踪**：显示对象创建和销毁过程
- **事件流追踪**：显示事件的绑定和触发过程
- **类型系统验证**：展示编译时类型检查

## 构建和运行

### 前置要求
- C++20兼容的编译器（GCC 10+, Clang 12+, MSVC 2019+）
- CMake 3.23+

### 构建步骤

```bash
# 使用构建脚本（推荐）
./build.sh

# 或者手动构建
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
make -j4
```

### 运行

```bash
cd build
./bin/wxui_explorer
```

## 输出示例

运行程序后，你会看到类似这样的输出：

```
=== wxUI Mock Explorer Starting ===
[App] wxApp created
[App] OnInit() called

--- Creating Explorer Frame ---
[Frame] Created frame with title: 'wxUI Mock Explorer'
[Frame] Created status bar with 1 fields
[Frame] Status bar field 0: 'Welcome to wxUI Mock Explorer!'

=== Starting wxUI Exploration Tests ===

--- Test 1: Basic Widget Creation ---
Creating basic widgets...
[Button] Created button with label: 'Test Button'
[StaticText] Created with text: 'Hello wxUI!'
[TextCtrl] Created with initial value: 'Initial text'
[CheckBox] Created with label: 'Check me'
✓ Basic widgets created successfully

--- Test 2: Layout System ---
Creating layout hierarchy...
[BoxSizer] Created vertical box sizer
[StaticText] Created with text: 'Layout Test Header'
[StaticBox] Created static box with label: 'Horizontal Section'
[StaticBoxSizer] Created with label: Horizontal Section
[Button] Created button with label: 'Left'
[Button] Created button with label: 'Center'
[Button] Created button with label: 'Right'
[Sizer] Adding window to sizer with flags
[Sizer] Adding window to sizer with flags
[Sizer] Adding window to sizer with flags
[Window] Sizer attached to window
[Sizer] Setting size hints for window
✓ Layout system working correctly
```

## 学习要点

### 1. CRTP模式的应用
观察`WidgetDetails`如何使用CRTP实现编译时多态：
```cpp
template <typename ConcreteWidget, typename Underlying>
struct WidgetDetails {
    auto withFlags(wxSizerFlags flags) & -> ConcreteWidget& {
        return static_cast<ConcreteWidget&>(*this);  // CRTP核心
    }
};
```

### 2. 类型擦除技术
观察`BindInfo`如何使用类型擦除存储不同类型的事件处理器：
```cpp
struct BindInfo {
    template <typename Event, typename Function>
    BindInfo(Event event, Function function);  // 类型擦除入口
};
```

### 3. 完美转发的使用
观察Layout系统如何使用完美转发保持参数语义：
```cpp
template <details::SizerItem... UItems>
explicit VSizer(UItems&&... items)
    : super(std::forward<UItems>(items)...) {}
```

### 4. 概念约束的作用
观察编译时如何通过Concepts确保类型安全：
```cpp
template <typename T>
concept CreateAndAddable = requires(T widget, wxWindow* window, wxSizer* sizer) {
    widget.createAndAdd(window, sizer, wxSizerFlags {});
};
```

## 扩展实验

你可以尝试以下实验来加深理解：

1. **添加新控件**：实现一个新的Mock控件，观察集成过程
2. **修改事件系统**：添加新的事件类型，观察类型擦除的工作
3. **扩展Proxy系统**：为控件添加新的访问器，观察GetterSetter的工作
4. **性能分析**：添加计时代码，观察编译时优化的效果

## 技术亮点

- **零依赖**：不需要安装wxWidgets即可运行
- **教学友好**：详细的日志输出便于理解
- **架构清晰**：Mock实现突出了关键的设计模式
- **扩展性强**：易于添加新的测试和实验

这个项目为深入理解wxUI的实现原理提供了一个理想的学习环境！
