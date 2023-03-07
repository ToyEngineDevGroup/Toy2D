#include "runtime/function/scripting/lua_binder.h"
#include "runtime/function/scripting/binder/lua_math_binder.h"

namespace Toy2D {
    void LuaBinder::callBinders(sol::state& p_luaState) {
        auto& L = p_luaState;

        LuaMathBinder::bindMaths(L);
    }
} // namespace Toy2D