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

namespace Layout {
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

    enum class Direction {
        Row,
        Column
    };

    enum class Wrap {
        NoWrap,
        Wrap
    };

    enum class Justify {
        Start,
        Center,
        End,
        SpaceBetween,
        SpaceAround,
        SpaceEvenly
    };

    enum class Align {
        Start,
        Center,
        End,
        Stretch,
        Baseline
    };
}

} // namespace Gui