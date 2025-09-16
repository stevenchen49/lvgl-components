#!/bin/bash

echo "=== Building wxUI Mock Explorer ==="

# 创建构建目录
mkdir -p build
cd build

# 配置CMake
echo "Configuring with CMake..."
cmake .. -DCMAKE_BUILD_TYPE=Debug

# 编译
echo "Building..."
make -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)

if [ $? -eq 0 ]; then
    echo "✓ Build successful!"
    echo ""
    echo "Run the explorer with:"
    echo "  ./bin/wxui_explorer"
    echo ""
else
    echo "✗ Build failed!"
    exit 1
fi
