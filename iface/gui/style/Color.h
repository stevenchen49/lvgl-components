#pragma once

#include <cstdint>

namespace gui{
namespace style {

struct Color
{
    uint32_t value;

    static constexpr uint32_t Transparent   = 0x00000000; //
    static constexpr uint32_t Black         = 0xFF000000; // #000000
    static constexpr uint32_t White         = 0xFFFFFFFF; // #FFFFFF
    static constexpr uint32_t Red           = 0xFFFF0000; // #FF0000
    static constexpr uint32_t Green         = 0xFF00FF00; // #00FF00
    static constexpr uint32_t Blue          = 0xFF0000FF; // #0000FF

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
};

} // namespace style
} // namespace gui