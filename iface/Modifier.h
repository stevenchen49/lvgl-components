#pragma once

#include "Adaptor.h"
#include "Style.h"

#include <functional>
#include <vector>

namespace Gui {

template <typename Derived>
class Modifier 
{
public:
    using Func = std::function<void(lv_obj_t*)>;

    virtual ~Modifier() = default;

public:
    Derived& size(const Size& size) &
    {
        custom([size](lv_obj_t* obj) {
            _lvSetSize(obj, size);
        });
        return static_cast<Derived&>(*this);
    }
    Derived&& size(const Size& size) &&
    {
        return std::move(static_cast<Derived&>(*this).size(size));
    }

    Derived& width(int width) &
    {
        custom([width](lv_obj_t* obj) {
            _lvSetWidth(obj, width);
        });
        return static_cast<Derived&>(*this);
    }
    Derived&& width(int width) &&
    {
        return std::move(static_cast<Derived&>(*this).width(width));
    }

    Derived& height(int height) &
    {
        custom([height](lv_obj_t* obj) {
            _lvSetHeight(obj, height);
        });
        return static_cast<Derived&>(*this);
    }
    Derived&& height(int height) &&
    {
        return std::move(static_cast<Derived&>(*this).height(height));
    }

    Derived& bgColor(lv_color_t color) &
    {
        custom([color](lv_obj_t* obj) {
            _lvSetBgColor(obj, color);
        });
        return static_cast<Derived&>(*this);
    }
    Derived&& bgColor(lv_color_t color) &&
    {
        return std::move(static_cast<Derived&>(*this).bgColor(color));
    }

public:
    Derived& custom(Func func) &
    {
        mFuncs.push_back(std::move(func));
        return static_cast<Derived&>(*this);
    }
    Derived&& custom(Func func) &&
    {
        return std::move(static_cast<Derived&>(*this).custom(func));
    }

    Derived& condition(bool condition, Func func) &
    {
        if (condition) {
            mFuncs.push_back(std::move(func));
        }
        return static_cast<Derived&>(*this);
    }
    Derived&& condition(bool condition, Func func) &&
    {
        return std::move(static_cast<Derived&>(*this).condition(condition, func));
    }

protected:
    void _applyAllModifiers(lv_obj_t* obj)
    {
        for (auto& func : mFuncs) {
            func(obj);
        }
    }

private:
    std::vector<Func> mFuncs;
};

} // namespace Gui