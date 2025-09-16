#!/bin/bash

echo "=== Building LVGL Modern ==="

# 创建构建目录
mkdir -p build
cd build

# 配置CMake
echo "Configuring with CMake..."
cmake .. -DCMAKE_BUILD_TYPE=Release -DLVGL_MODERN_BUILD_EXAMPLES=ON

# 编译
echo "Building..."
make -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)

if [ $? -eq 0 ]; then
    echo "✓ Build successful!"
    echo ""
    echo "Run examples with:"
    echo "  ./bin/basic_example"
    echo "  ./bin/threading_example"
    echo ""
else
    echo "✗ Build failed!"
    exit 1
fi
