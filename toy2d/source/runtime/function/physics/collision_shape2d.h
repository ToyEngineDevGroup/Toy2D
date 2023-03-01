#pragma once

#include <box2d/box2d.h>
#include "runtime/core/base/core.h"

namespace Toy2D{
    class CollisionShape2D {
    public:
        CollisionShape2D();
        void createBox(float w, float h);
        Scope<b2Shape> m_b2shape;
    };
};
