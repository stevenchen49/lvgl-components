# wxUI 核心设计思路文档

## 概述

wxUI是一个C++头文件库，旨在为wxWidgets提供声明式UI构建能力。它通过现代C++技术（C++20）实现了一套优雅的API，让开发者能够以更直观、更简洁的方式构建用户界面。

## 核心设计理念

### 1. 声明式编程范式

**传统wxWidgets方式**：
```cpp
// 分离的"创建"和"布局"阶段
auto* text = new wxStaticText(this, wxID_ANY, "Hello");
auto* button = new wxButton(this, wxID_ANY, "Click");
auto* sizer = new wxBoxSizer(wxVERTICAL);
sizer->Add(text, wxSizerFlags().Expand().Border());
sizer->Add(button, wxSizerFlags().Center());
SetSizerAndFit(sizer);
```

**wxUI声明式方式**：
```cpp
// 结构化声明，代码即布局
VSizer {
    Text { "Hello" },
    Button { "Click" }.bind([]{ /* action */ })
}.fitTo(this);
```

**设计优势**：
- **代码即文档**：UI结构在代码中一目了然
- **减少样板代码**：自动处理对象创建、内存管理和布局
- **降低错误率**：减少手动管理指针和布局的机会

### 2. 工厂模式与延迟构造

wxUI采用"蓝图"模式，对象在声明时不立即创建wxWidgets控件，而是在调用`fitTo()`时才实际构造：

```cpp
// 这里只是创建了"蓝图"
auto layout = VSizer {
    Text { "Hello" },
    Button { "World" }
};

// 这里才真正创建wxWidgets对象
layout.fitTo(parentWindow);
```

**核心实现机制**：
- `createAndAdd(wxWindow* parent, wxSizer* sizer, wxSizerFlags flags)` 接口
- 递归构造：从顶层Layout开始，递归创建所有子组件
- 自动内存管理：wxWidgets的父子关系自动管理对象生命周期

### 3. 类型安全的组合设计

#### Layout层次结构
```cpp
namespace wxUI {
    // 基础布局类型
    struct VSizer;    // 垂直布局
    struct HSizer;    // 水平布局
    struct FlexGridSizer; // 网格布局
    
    // 特殊布局
    struct HSplitter; // 水平分割器
    struct VSplitter; // 垂直分割器
    struct Generic;   // 通用容器
}
```

#### Controller层次结构
```cpp
// 所有控件都继承自WidgetDetails基类
template<typename Derived, typename UnderlyingWidget>
struct WidgetDetails {
    // 通用方法链接口
    auto withFlags(wxSizerFlags) -> Derived&;
    auto withStyle(long) -> Derived&;
    auto withSize(wxSize) -> Derived&;
    // ...
};

// 具体控件实现
struct Button : WidgetDetails<Button, wxButton> { /* ... */ };
struct Text : WidgetDetails<Text, wxStaticText> { /* ... */ };
```

### 4. 方法链式API设计

wxUI大量使用方法链模式，提供流畅的API体验：

```cpp
Button { "Submit" }
    .withSize(wxSize(100, 30))
    .withStyle(wxBU_EXACTFIT)
    .setDefault()
    .bind([](){ /* 处理点击 */ });
```

**实现技巧**：
- 返回引用的左值版本：`auto method() & -> Derived&`
- 返回移动的右值版本：`auto method() && -> Derived&&`
- 支持链式调用的同时保持性能

### 5. 代理模式（Proxy Pattern）

为了在声明式结构中访问运行时对象，wxUI设计了Proxy系统：

```cpp
class MyDialog : public wxDialog {
    wxUI::Text::Proxy textProxy;
    wxUI::SpinCtrl::Proxy spinProxy;
    
public:
    MyDialog() {
        VSizer {
            Text { "Initial" }.withProxy(textProxy),
            SpinCtrl { {1, 100} }.withProxy(spinProxy)
                .bind([this]() {
                    *textProxy = std::to_string(*spinProxy);
                })
        }.fitTo(this);
    }
};
```

**Proxy设计特点**：
- **类型安全**：每个控件有对应的Proxy类型
- **延迟绑定**：Proxy在`withProxy()`时绑定到实际控件
- **智能访问**：重载`operator*`和`operator->`提供自然语法
- **多值访问**：支持`value()`、`selection()`等多个访问器

### 6. 事件绑定的现代化

#### 传统wxWidgets事件处理
```cpp
// 需要定义事件ID和处理函数
enum { ID_BUTTON = 1000 };
button->Bind(wxEVT_BUTTON, &MyClass::OnButton, this, ID_BUTTON);
```

#### wxUI事件绑定
```cpp
Button { "Click" }
    .bind([]() { /* 简单处理 */ })
    .bind([](wxCommandEvent& e) { /* 需要事件参数 */ });
```

**设计优势**：
- **自动ID管理**：无需手动管理事件ID
- **Lambda友好**：直接支持lambda表达式
- **参数可选**：可以省略不需要的事件参数
- **多事件绑定**：同一控件可绑定多个事件

### 7. 模板元编程与概念约束

wxUI大量使用C++20的概念（Concepts）来确保类型安全：

```cpp
template <typename T>
concept CreateAndAddable = requires(T widget, wxWindow* window, wxSizer* sizer) {
    widget.createAndAdd(window, sizer, wxSizerFlags {});
};

template <typename T>
concept SizerItem = CreateAndAddable<T> 
    || (std::is_pointer_v<T> && std::derived_from<std::remove_pointer_t<T>, wxSizer>);
```

**编译时保证**：
- 只有符合接口的类型才能用于布局
- 提供清晰的编译错误信息
- 支持类型推导和完美转发

## 核心组件架构

### 1. Layout系统

```
Layout (抽象概念)
├── Sizer (基础布局)
│   ├── VSizer (垂直布局)
│   ├── HSizer (水平布局)
│   └── FlexGridSizer (网格布局)
├── Splitter (分割布局)
│   ├── HSplitter
│   └── VSplitter
└── Special (特殊布局)
    ├── Generic (通用容器)
    ├── ForEach (循环布局)
    └── LayoutIf (条件布局)
```

### 2. Controller系统

```
WidgetDetails<Derived, UnderlyingWidget>
├── 输入控件
│   ├── TextCtrl (文本输入)
│   ├── SpinCtrl (数字输入)
│   ├── ComboBox (组合框)
│   └── Choice (选择框)
├── 选择控件
│   ├── CheckBox (复选框)
│   ├── RadioBox (单选框组)
│   └── ListBox (列表框)
├── 按钮控件
│   ├── Button (普通按钮)
│   ├── BitmapButton (图片按钮)
│   └── BitmapToggleButton (切换按钮)
├── 显示控件
│   ├── Text (静态文本)
│   ├── Bitmap (图片显示)
│   ├── Line (分割线)
│   └── Gauge (进度条)
└── 其他控件
    ├── Hyperlink (超链接)
    └── Slider (滑块)
```

### 3. Menu系统

```cpp
MenuBar {
    Menu {
        "&File",
        Item { "&New", []() { /* 新建 */ } },
        Separator {},
        Item { wxID_EXIT, [](){ /* 退出 */ } }
    },
    Menu {
        "&Edit", 
        CheckItem { "&Word Wrap", [](wxCommandEvent& e) { 
            /* 处理选中状态 */ 
        }},
        Menu {
            "Sub Menu",
            RadioItem { "Option 1", [](){} },
            RadioItem { "Option 2", [](){} }
        }
    }
}.fitTo(frame);
```

## 高级特性

### 1. ForEach循环构造

```cpp
// 动态生成按钮
HSizer {
    ForEach {
        std::vector{"Red", "Green", "Blue"},
        [](auto color) {
            return Button { color }
                .bind([color]() { 
                    wxLogMessage("Selected %s", color); 
                });
        }
    }
}
```

### 2. 条件布局

```cpp
bool showAdvanced = true;
VSizer {
    Text { "Basic Options" },
    LayoutIf { showAdvanced,
        Text { "Advanced Options" },
        SpinCtrl { {1, 100} }
    }
}
```

### 3. 自定义控件集成

```cpp
HSizer {
    Custom {
        [](wxWindow* parent, wxSizer* sizer, wxSizerFlags flags) {
            // 创建复杂的自定义控件
            auto* custom = new MyCustomWidget(parent);
            sizer->Add(custom, flags);
        }
    }
}
```

## 内存管理策略

### 1. RAII原则
- 所有wxUI对象都是值语义，自动管理生命周期
- wxWidgets对象通过父子关系自动管理内存
- Proxy对象使用智能指针避免悬挂引用

### 2. 移动语义优化
```cpp
// 支持完美转发，避免不必要的拷贝
template<typename... Args>
VSizer(Args&&... args) 
    : items_(std::forward_as_tuple(std::forward<Args>(args)...)) {}
```

### 3. 异常安全
- 构造失败时自动清理已创建的对象
- Proxy访问未绑定对象时抛出异常而非崩溃

## 性能考虑

### 1. 编译时优化
- 大量使用模板和constexpr减少运行时开销
- 概念约束提供编译时类型检查
- 完美转发避免不必要的对象拷贝

### 2. 运行时效率
- 延迟构造：只在需要时创建wxWidgets对象
- 事件绑定优化：避免虚函数调用开销
- 内存局部性：相关对象在内存中紧密排列

## 扩展性设计

### 1. 新控件添加
```cpp
// 添加新控件只需继承WidgetDetails
struct MyWidget : WidgetDetails<MyWidget, wxMyWidget> {
    // 实现createImpl方法
    auto createImpl(wxWindow* parent) -> wxWindow* override {
        return new wxMyWidget(parent, getIdentity(), /* ... */);
    }
};
```

### 2. 新布局类型
```cpp
// 添加新布局类型
struct MyLayout : details::Sizer<Items...> {
    auto constructSizer(wxWindow* parent) const -> wxSizer* override {
        return new wxMyCustomSizer(parent);
    }
};
```

## 与wxWidgets的互操作

### 1. 渐进式采用
```cpp
// 可以在传统wxWidgets代码中局部使用wxUI
auto* panel = new wxPanel(parent);
wxUI::HSizer {
    wxUI::Button { "OK" },
    wxUI::Button { "Cancel" }
}.fitTo(panel);
```

### 2. 直接访问底层对象
```cpp
wxUI::Button::Proxy buttonProxy;
// ... 绑定后
buttonProxy->SetLabel("New Label");  // 直接调用wxButton方法
```

## 总结

wxUI的核心设计思路体现了现代C++的最佳实践：

1. **声明式编程**：让代码结构直接反映UI结构
2. **类型安全**：编译时捕获错误，运行时保证正确性
3. **零成本抽象**：高级API不牺牲性能
4. **渐进式采用**：可以与现有wxWidgets代码无缝集成
5. **扩展友好**：易于添加新控件和新功能

这种设计让wxWidgets的使用变得更加现代化和用户友好，同时保持了与底层框架的完全兼容性。
