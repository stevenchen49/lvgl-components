# GUI 组件系统 CMakeLists.txt

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 接口层 - 头文件
set(COMPONENT_IFACE_HEADERS
    iface/ComponentConfig.h
    iface/Component.h
    iface/ColorConfig.h
    iface/ButtonConfig.h
    iface/Button.h
)

# 接口层 - 源文件
set(COMPONENT_IFACE_SOURCES
    iface/Button.cpp
    iface/Checkbox.cpp
    iface/Radio.cpp
    iface/Switch.cpp
)

# 实现层 - LV8 源文件
set(COMPONENT_LV8_SOURCES
    impls/lv8/ComponentLv8.cpp
    impls/lv8/ButtonLv8.cpp
    impls/lv8/CheckboxLv8.cpp
    impls/lv8/RadioLv8.cpp
    impls/lv8/SwitchLv8.cpp
)

# 创建接口库
add_library(component_iface STATIC ${COMPONENT_IFACE_SOURCES})
target_include_directories(component_iface PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/iface
    ${CMAKE_CURRENT_SOURCE_DIR}/../lvgl
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

# 创建 LV8 实现库
add_library(component_lv8 STATIC ${COMPONENT_LV8_SOURCES})
target_include_directories(component_lv8 PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/iface
    ${CMAKE_CURRENT_SOURCE_DIR}/../lvgl
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

# 链接依赖
target_link_libraries(component_lv8 component_iface)

# 设置编译选项
target_compile_definitions(component_iface PRIVATE LV_CONF_INCLUDE_SIMPLE)
target_compile_definitions(component_lv8 PRIVATE LV_CONF_INCLUDE_SIMPLE)

# 导出库
set_target_properties(component_iface PROPERTIES
    EXPORT_NAME "ComponentInterface"
    VERSION 1.0.0
    SOVERSION 1
)

set_target_properties(component_lv8 PROPERTIES
    EXPORT_NAME "ComponentLv8"
    VERSION 1.0.0
    SOVERSION 1
)

# 安装规则（简化版本）
# install(TARGETS component_iface component_lv8
#     LIBRARY DESTINATION lib
#     ARCHIVE DESTINATION lib
#     RUNTIME DESTINATION bin
#     INCLUDES DESTINATION include
# )
