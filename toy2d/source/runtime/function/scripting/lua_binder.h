#pragma once

#include <sol/sol.hpp>

namespace Toy2D {
    class LuaBinder {
    public:
        static void callBinders(sol::state& p_luaState);
    };
} // namespace Toy2D