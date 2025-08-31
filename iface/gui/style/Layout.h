#pragma once

namespace gui {
namespace style {

struct Layout 
{
    enum class Horizontal {
        Leading,
        Center,
        Trailing
    };

    enum class Vertical {
        Top,
        Center,
        Bottom
    };
};

} // namespace style
} // namespace gui