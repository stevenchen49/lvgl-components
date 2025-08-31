#pragma once

#include "Adaptor.h"

#include <functional>
#include <vector>

namespace gui {

template <typename Derived>
class Modifier 
{
public:
    using Func = std::function<void(lv_obj_t*)>;

    Modifier() = default;
    virtual ~Modifier() = default;

    Modifier(Modifier&&) noexcept = default;
    Modifier& operator=(Modifier&&) noexcept = default;
    Modifier(const Modifier&) = delete;
    Modifier& operator=(const Modifier&) = delete;

public:
    template<class Fn, class... Args>
    Derived& custom(Fn&& fn, Args&&... args) & 
    {
        using FnD = std::decay_t<Fn>;
        using Tup = std::tuple<std::decay_t<Args>...>;

        FnD fnCopy(std::forward<Fn>(fn));         
        Tup data(std::forward<Args>(args)...);     
        mFuncs.emplace_back([f = std::move(fnCopy), d = std::move(data)](lv_obj_t* obj) mutable {
            std::apply([&](auto&... xs){ std::invoke(f, obj, xs...); }, d);
        });

        return lself();
    }

    template<class Fn, class... Args>
    Derived&& custom(Fn&& fn, Args&&... args) && 
    {
        custom(std::forward<Fn>(fn), std::forward<Args>(args)...);
        return rself();
    }

protected:
    Derived& lself() { return static_cast<Derived&>(*this); }
    Derived&& rself() { return static_cast<Derived&&>(*this); }

    void _applyAllModifiers(lv_obj_t* obj)
    {
        for (auto& func : mFuncs) {
            func(obj);
        }
    }

private:
    std::vector<Func> mFuncs;
};

} // namespace gui