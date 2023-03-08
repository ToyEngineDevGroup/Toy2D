#pragma once

#include <sol/sol.hpp>

namespace Toy2D {
    class LuaEntityBinder {
    public:
        static void bindEntity(sol::state& p_luaState);
    };
} // namespace Toy2D