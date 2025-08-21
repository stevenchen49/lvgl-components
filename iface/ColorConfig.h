#pragma once

#include <cstdint>

namespace Gui
{

/**
 * @brief 颜色配置类 - 基于 Bambu Lab H2D 打印机 UI 设计
 * 
 * 颜色系统采用 ARGB8888 格式 (0xAARRGGBB)
 * 主要特点：
 * - 深色主题为主
 * - 橙色品牌色
 * - 完整的功能色系统
 * - 9级灰度层次
 */
struct ColorConfig 
{
    uint32_t value;

    // ==================== 品牌色 (Brand Colors) ====================
    
    /// @brief 主品牌色 - Bambu Lab 橙色
    static const uint32_t Primary = 0xFFF7931E;
    
    /// @brief 次要品牌色 - 深橙色
    static const uint32_t Secondary = 0xFFE67E22;
    
    /// @brief 品牌色变体 - 浅橙色
    static const uint32_t PrimaryLight = 0xFFFFA726;
    
    /// @brief 品牌色变体 - 深橙色
    static const uint32_t PrimaryDark = 0xFFE65100;

    // ==================== 功能色 (Functional Colors) ====================
    
    /// @brief 成功色 - 绿色
    static const uint32_t Success = 0xFF4CAF50;
    
    /// @brief 警告色 - 黄色
    static const uint32_t Warning = 0xFFFF9800;
    
    /// @brief 错误色 - 红色
    static const uint32_t Error = 0xFFF44336;
    
    /// @brief 信息色 - 蓝色
    static const uint32_t Info = 0xFF2196F3;
    
    /// @brief 链接色 - 浅蓝色
    static const uint32_t Link = 0xFF03A9F4;

    // ==================== 灰度系统 (Grey Scale) ====================
    
    /// @brief 最浅灰色 - 接近白色
    static const uint32_t Grey100 = 0xFFF5F5F5;
    
    /// @brief 浅灰色
    static const uint32_t Grey200 = 0xFFEEEEEE;
    
    /// @brief 中浅灰色
    static const uint32_t Grey300 = 0xFFE0E0E0;
    
    /// @brief 中等灰色
    static const uint32_t Grey400 = 0xFFBDBDBD;
    
    /// @brief 中深灰色
    static const uint32_t Grey500 = 0xFF9E9E9E;
    
    /// @brief 深灰色
    static const uint32_t Grey600 = 0xFF757575;
    
    /// @brief 更深灰色
    static const uint32_t Grey700 = 0xFF616161;
    
    /// @brief 深灰色
    static const uint32_t Grey800 = 0xFF424242;
    
    /// @brief 最深灰色 - 接近黑色
    static const uint32_t Grey900 = 0xFF212121;

    // ==================== 背景色 (Background Colors) ====================
    
    /// @brief 主背景色 - 深蓝灰色
    static const uint32_t Background = 0xFF1E1E2E;
    
    /// @brief 次要背景色 - 稍浅的深色
    static const uint32_t BackgroundSecondary = 0xFF2D2D44;
    
    /// @brief 卡片背景色
    static const uint32_t CardBackground = 0xFF2A2A3C;
    
    /// @brief 弹出框背景色
    static const uint32_t ModalBackground = 0xFF1A1A2A;

    // ==================== 文本色 (Text Colors) ====================
    
    /// @brief 主要文本色 - 白色
    static const uint32_t TextPrimary = 0xFFFFFFFF;
    
    /// @brief 次要文本色 - 浅灰色
    static const uint32_t TextSecondary = 0xFFB0B0B0;
    
    /// @brief 禁用文本色 - 深灰色
    static const uint32_t TextDisabled = 0xFF666666;
    
    /// @brief 链接文本色
    static const uint32_t TextLink = 0xFF03A9F4;

    // ==================== 边框色 (Border Colors) ====================
    
    /// @brief 主要边框色
    static const uint32_t BorderPrimary = 0xFF3A3A4A;
    
    /// @brief 次要边框色
    static const uint32_t BorderSecondary = 0xFF2A2A3A;
    
    /// @brief 焦点边框色 - 使用品牌色
    static const uint32_t BorderFocus = 0xFFF7931E;

    // ==================== 状态色 (State Colors) ====================
    
    /// @brief 悬停状态色
    static const uint32_t Hover = 0xFF3A3A4A;
    
    /// @brief 按下状态色
    static const uint32_t Pressed = 0xFF2A2A3A;
    
    /// @brief 选中状态色
    static const uint32_t Selected = 0xFFF7931E;
    
    /// @brief 禁用状态色
    static const uint32_t Disabled = 0xFF1A1A2A;

    // ==================== 特殊用途色 (Special Purpose Colors) ====================
    
    /// @brief 阴影色
    static const uint32_t Shadow = 0x80000000;
    
    /// @brief 高亮色
    static const uint32_t Highlight = 0x33F7931E;
    
    /// @brief 覆盖层色
    static const uint32_t Overlay = 0xCC000000;
    
    /// @brief 透明色
    static const uint32_t Transparent = 0x00000000;

    // ==================== 打印状态色 (Print Status Colors) ====================
    
    /// @brief 打印中 - 蓝色
    static const uint32_t PrintInProgress = 0xFF2196F3;
    
    /// @brief 打印完成 - 绿色
    static const uint32_t PrintCompleted = 0xFF4CAF50;
    
    /// @brief 打印失败 - 红色
    static const uint32_t PrintFailed = 0xFFF44336;
    
    /// @brief 打印暂停 - 黄色
    static const uint32_t PrintPaused = 0xFFFF9800;
    
    /// @brief 预热中 - 橙色
    static const uint32_t Preheating = 0xFFFF5722;

    // ==================== 温度相关色 (Temperature Colors) ====================
    
    /// @brief 低温 - 蓝色
    static const uint32_t TempLow = 0xFF2196F3;
    
    /// @brief 中温 - 黄色
    static const uint32_t TempMedium = 0xFFFF9800;
    
    /// @brief 高温 - 红色
    static const uint32_t TempHigh = 0xFFF44336;
    
    /// @brief 超高温 - 深红色
    static const uint32_t TempCritical = 0xFFD32F2F;

    // ==================== 辅助方法 (Helper Methods) ====================
    
    /**
     * @brief 创建带透明度的颜色
     * @param color 基础颜色
     * @param alpha 透明度 (0-255)
     * @return 带透明度的颜色
     */
    static uint32_t withAlpha(uint32_t color, uint8_t alpha) {
        return (color & 0x00FFFFFF) | (static_cast<uint32_t>(alpha) << 24);
    }
    
    /**
     * @brief 创建半透明颜色
     * @param color 基础颜色
     * @return 半透明颜色
     */
    static uint32_t semiTransparent(uint32_t color) {
        return withAlpha(color, 128);
    }
    
    /**
     * @brief 获取红色分量
     * @param color 颜色值
     * @return 红色分量 (0-255)
     */
    static uint8_t getRed(uint32_t color) {
        return static_cast<uint8_t>((color >> 16) & 0xFF);
    }
    
    /**
     * @brief 获取绿色分量
     * @param color 颜色值
     * @return 绿色分量 (0-255)
     */
    static uint8_t getGreen(uint32_t color) {
        return static_cast<uint8_t>((color >> 8) & 0xFF);
    }
    
    /**
     * @brief 获取蓝色分量
     * @param color 颜色值
     * @return 蓝色分量 (0-255)
     */
    static uint8_t getBlue(uint32_t color) {
        return static_cast<uint8_t>(color & 0xFF);
    }
    
    /**
     * @brief 获取透明度分量
     * @param color 颜色值
     * @return 透明度分量 (0-255)
     */
    static uint8_t getAlpha(uint32_t color) {
        return static_cast<uint8_t>((color >> 24) & 0xFF);
    }
};

} // namespace Gui