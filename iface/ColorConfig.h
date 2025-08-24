#pragma once

#include <cstdint>

namespace Gui
{

struct ColorConfig 
{
    uint32_t value;

    static constexpr uint32_t Black         = 0xFF000000; // #000000
    static constexpr uint32_t White         = 0xFFFFFFFF; // #FFFFFF
    static constexpr uint32_t Transparent   = 0x00000000; // 完全透明

    static constexpr uint32_t Grey50        = 0xFF141414; // #141414    
    static constexpr uint32_t Grey100       = 0xFF242424; // #242424
    static constexpr uint32_t Grey200       = 0xFF333333; // #333333
    static constexpr uint32_t Grey300       = 0xFF474747; // #474747
    static constexpr uint32_t Grey400       = 0xFF5C5C5C; // #5C5C5C
    static constexpr uint32_t Grey500       = 0xFF707070; // #707070
    static constexpr uint32_t Grey600       = 0xFF8A8A8A; // #8A8A8A
    static constexpr uint32_t Grey700       = 0xFFA3A3A3; // #A3A3A3
    static constexpr uint32_t Grey800       = 0xFFCCCCCC; // #CCCCCC
    static constexpr uint32_t Grey900       = 0xFFE0E0E0; // #E0E0E0

    static constexpr uint32_t Brand         = 0xFFA5F960; // #A5F960
    static constexpr uint32_t Primary       = 0xFF000000; // #000000
    static constexpr uint32_t Secondary     = 0xFF8AA97c; // #8AA97C

    static constexpr uint32_t Info          = 0xFF0E65E9; // #0E65E9
    static constexpr uint32_t Warning       = 0xFFF09A17; // #F09A17
    static constexpr uint32_t Danger        = 0xFFE14747; // #E14747

    static constexpr uint32_t BgBase        = Grey50;
    static constexpr uint32_t BgMiddle      = Grey100; 
    static constexpr uint32_t BgTop         = Grey200; 

    /**
     * @brief 创建带透明度的颜色
     * @param color 基础颜色
     * @param alpha 透明度 (0-255)
     * @return 带透明度的颜色
     */
    static uint32_t withAlpha(uint32_t color, uint8_t alpha) 
    {
        return (color & 0x00FFFFFF) | (static_cast<uint32_t>(alpha) << 24);
    }
    
    /**
     * @brief 创建半透明颜色
     * @param color 基础颜色
     * @return 半透明颜色
     */
    static uint32_t semiTransparent(uint32_t color) 
    {
        return withAlpha(color, 128);
    }
    
    /**
     * @brief 获取红色分量
     * @param color 颜色值
     * @return 红色分量 (0-255)
     */
    static uint8_t getRed(uint32_t color) 
    {
        return static_cast<uint8_t>((color >> 16) & 0xFF);
    }
    
    /**
     * @brief 获取绿色分量
     * @param color 颜色值
     * @return 绿色分量 (0-255)
     */
    static uint8_t getGreen(uint32_t color) 
    {
        return static_cast<uint8_t>((color >> 8) & 0xFF);
    }
    
    /**
     * @brief 获取蓝色分量
     * @param color 颜色值
     * @return 蓝色分量 (0-255)
     */
    static uint8_t getBlue(uint32_t color) 
    {
        return static_cast<uint8_t>(color & 0xFF);
    }
    
    /**
     * @brief 获取透明度分量
     * @param color 颜色值
     * @return 透明度分量 (0-255)
     */
    static uint8_t getAlpha(uint32_t color) 
    {
        return static_cast<uint8_t>((color >> 24) & 0xFF);
    }
};

} // namespace Gui