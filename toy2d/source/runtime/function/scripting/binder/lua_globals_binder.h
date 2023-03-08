#pragma once

#include <sol/sol.hpp>

namespace Toy2D {
    class LuaGlobalsBinder {
    public:
        static void bindGlobals(sol::state& p_luaState);
    };
} // namespace Toy2D