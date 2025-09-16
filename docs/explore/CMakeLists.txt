cmake_minimum_required(VERSION 3.23)
project(wxUI_Mock_Explorer VERSION 0.1)

# 设置C++标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 编译选项
if(NOT MSVC)
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 包含目录
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

# 创建可执行文件
add_executable(wxui_explorer
    src/main.cpp
    src/MockWidgets.cpp
    src/ExplorerApp.cpp
)

# 链接库（这里我们不需要真正的wxWidgets）
target_compile_definitions(wxui_explorer PRIVATE WXUI_MOCK_MODE=1)

# 设置输出目录
set_target_properties(wxui_explorer PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
