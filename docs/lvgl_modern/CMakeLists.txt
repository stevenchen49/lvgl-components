cmake_minimum_required(VERSION 3.20)
project(LVGL_Modern VERSION 1.0.0)

# 设置C++标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 编译选项
if(NOT MSVC)
    add_compile_options(-Wall -Wextra -Wpedantic)
    # 禁用一些过于严格的警告
    add_compile_options(-Wno-unused-parameter -Wno-unused-variable)
endif()

# 包含目录
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 创建头文件库
add_library(lvgl_modern INTERFACE)
target_include_directories(lvgl_modern INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 设置C++20要求
target_compile_features(lvgl_modern INTERFACE cxx_std_20)

# 链接线程库
find_package(Threads REQUIRED)
target_link_libraries(lvgl_modern INTERFACE Threads::Threads)

# 示例程序
option(LVGL_MODERN_BUILD_EXAMPLES "Build example programs" ON)

if(LVGL_MODERN_BUILD_EXAMPLES)
    # 基础示例
    add_executable(basic_example examples/basic_example.cpp)
    target_link_libraries(basic_example lvgl_modern)
    
    # 线程安全示例
    add_executable(threading_example examples/threading_example.cpp)
    target_link_libraries(threading_example lvgl_modern)
    
    # 设置输出目录
    set_target_properties(basic_example threading_example PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    )
endif()