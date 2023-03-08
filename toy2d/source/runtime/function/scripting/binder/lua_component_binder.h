#pragma once

#include <sol/sol.hpp>

namespace Toy2D {
    class LuaComponentBinder {
    public:
        static void bindComponent(sol::state& p_luaState);
    };
} // namespace Toy2D