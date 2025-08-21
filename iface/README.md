# GUI 组件系统

基于 LVGL 的现代化 GUI 组件系统，提供配置化的组件创建和事件处理。

## 目录结构

```
components/
├── iface/                    # 接口层
│   ├── ComponentConfig.h     # 配置结构体
│   ├── Component.h          # 组件基类声明
│   ├── Component.cpp        # 组件基类实现
│   ├── ColorConfig.h        # 颜色配置
│   └── README.md            # 使用文档
└── impls/                   # 实现层
    └── lv8/                 # LVGL 8.x 实现
        └── ComponentLv8.cpp # LVGL 操作的静态 API
```

## 设计理念

### 🎯 **配置驱动**
- 通过 `ComponentConfig` 结构体配置组件属性
- 支持链式调用和流式 API
- 类型安全的配置系统

### 🎨 **颜色系统**
- 基于 Bambu Lab H2D 打印机 UI 设计的颜色方案
- 完整的品牌色、功能色、灰度系统
- 支持透明度调节

### 🔧 **事件处理**
- 函数式事件回调
- 支持点击、长按、焦点等事件
- 类型安全的事件处理

### 📱 **响应式布局**
- 弹性布局支持
- 自动尺寸调整
- 父子组件管理

### 🏗️ **分层架构**
- **接口层** (`iface/`): 定义组件接口和配置
- **实现层** (`impls/`): 不同版本的 LVGL 实现
- **版本隔离**: 支持多个 LVGL 版本共存

## 核心组件

### ComponentConfig
配置结构体，包含：
- **Pos**: 位置和尺寸
- **Layout**: 布局配置
- **Style**: 样式配置
- **Text**: 文本配置（可选，仅对支持文本的对象有效）
- **Event**: 事件配置
- **Animation**: 动画配置

### Component
组件基类，提供：
- 配置化创建
- 事件处理
- 样式管理
- 子组件管理



## 使用示例

### 基本用法

```cpp
#include "Component.h"
#include "ColorConfig.h"

// 创建配置
ComponentConfig config;
config.setPos(10, 10)
      .setSize(200, 100)
      .setBgColor(ColorConfig::Primary)
      .setTextColor(ColorConfig::TextPrimary)
      .setOnClick([](lv_event_t* e) {
          printf("Button clicked!\n");
      });

// 创建组件
auto component = std::make_shared<Component>(config);
component->createObject(parent_obj);
```



### 链式调用

```cpp
auto button = std::make_shared<Component>();
button->setPos(50, 50)
       .setSize(120, 40)
       .setBgColor(ColorConfig::Success)
       .setText("确认")
       .setOnClick([](lv_event_t* e) {
           // 处理点击事件
       })
       .createObject(parent);
```

### 样式配置

```cpp
ComponentConfig::Style style;
style.bgColor = ColorConfig::CardBackground;
style.textColor = ColorConfig::TextPrimary;
style.borderColor = ColorConfig::BorderPrimary;
style.borderWidth = 2;
style.radius = 8;
style.padding = 10;

ComponentConfig config;
config.style = style;
config.setText("卡片内容");
```

### 布局配置

```cpp
ComponentConfig::Layout layout;
layout.flexFlow = LV_FLEX_FLOW_COLUMN;
layout.mainPlace = LV_FLEX_ALIGN_CENTER;
layout.crossPlace = LV_FLEX_ALIGN_CENTER;
layout.rowGap = 10;

ComponentConfig config;
config.layout = layout;
```

## 颜色系统

### 品牌色
- `Primary`: Bambu Lab 橙色 `#F7931E`
- `Secondary`: 深橙色 `#E67E22`
- `PrimaryLight`: 浅橙色 `#FFA726`
- `PrimaryDark`: 深橙色 `#E65100`

### 功能色
- `Success`: 绿色 `#4CAF50`
- `Warning`: 黄色 `#FF9800`
- `Error`: 红色 `#F44336`
- `Info`: 蓝色 `#2196F3`
- `Link`: 浅蓝色 `#03A9F4`

### 灰度系统
- `Grey100` 到 `Grey900`: 9级灰度层次
- 从最浅的 `#F5F5F5` 到最深的 `#212121`

### 背景色
- `Background`: 主背景 `#1E1E2E`
- `CardBackground`: 卡片背景 `#2A2A3C`
- `ModalBackground`: 弹出框背景 `#1A1A2A`

## 事件处理

### 支持的事件类型
- `onClick`: 点击事件
- `onLongPress`: 长按事件
- `onFocus`: 获得焦点
- `onBlur`: 失去焦点
- `onValueChange`: 值变化

### 事件回调示例

```cpp
config.setOnClick([](lv_event_t* e) {
    lv_obj_t* obj = lv_event_get_target(e);
    printf("Object clicked: %p\n", obj);
});

config.setOnLongPress([](lv_event_t* e) {
    printf("Long press detected!\n");
});
```

## 子组件管理

```cpp
auto parent = std::make_shared<Component>();
parent->createObject(screen);

auto child1 = std::make_shared<Component>();
auto child2 = std::make_shared<Component>();

parent->addChild(child1);
parent->addChild(child2);

// 移除子组件
parent->removeChild(child1);
```

## 扩展组件

要创建自定义组件，继承 `Component` 类：

```cpp
class CustomButton : public Component {
public:
    CustomButton(const ComponentConfig& config) : Component(config) {}
    
    lv_obj_t* createObject(lv_obj_t* parent) override {
        // 创建自定义 LVGL 对象
        mLvObj = lv_button_create(parent);
        applyConfig();
        return mLvObj;
    }
};
```

## 最佳实践

1. **使用配置驱动**: 优先使用 `ComponentConfig` 进行配置
2. **链式调用**: 利用链式调用提高代码可读性
3. **颜色一致性**: 使用 `ColorConfig` 中的预定义颜色
4. **事件处理**: 使用 lambda 表达式处理事件
5. **内存管理**: 使用 `std::shared_ptr` 管理组件生命周期

## 注意事项

- 组件创建后会自动应用配置
- 事件回调中的 `this` 指针会被正确传递
- 子组件会在父组件销毁时自动清理
- 颜色值使用 ARGB8888 格式 (0xAARRGGBB)

## 关于文本功能

### 文本支持的局限性
在 LVGL 中，不是所有对象类型都支持文本功能：

**支持文本的对象**：
- `lv_label` - 专门用于显示文本
- `lv_button` - 可以设置按钮文本
- `lv_textarea` - 文本输入框
- `lv_dropdown` - 下拉菜单

**不支持文本的对象**：
- `lv_obj` - 基础对象，不直接支持文本
- `lv_image` - 图像对象
- `lv_chart` - 图表对象
- `lv_bar` - 进度条

### 解决方案
1. **智能检测**: 基础 Component 会检测对象类型，只对支持文本的对象设置文本
2. **配置可选**: 文本配置是可选的，只有启用时才会应用
3. **类型安全**: 避免了对不支持文本的对象设置文本

### 推荐用法
- 需要按钮时，使用专门的 `ButtonComponent`（可以包含文本）
- 通用容器使用基础 `Component`
- 文本显示可以通过配置的文本功能实现
