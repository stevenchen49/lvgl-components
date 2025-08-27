#pragma once

namespace Gui {

struct Size {
    int width;
    int height;
};

struct Position {
    int x;
    int y;
};

struct Layout {

};

enum class HorizontalAlignment {
    Leading,
    Center,
    Trailing
};

enum class VerticalAlignment {
    Top,
    Center,
    Bottom
};

} // namespace Gui