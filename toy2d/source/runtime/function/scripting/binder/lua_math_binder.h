#pragma once

#include <sol/sol.hpp>

namespace Toy2D {
    class LuaMathBinder {
    public:
        static void bindMaths(sol::state& p_luaState);
    };
} // namespace Toy2D