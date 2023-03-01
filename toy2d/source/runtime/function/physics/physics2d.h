#pragma once

#include <unordered_map>
#include <box2d/box2d.h>
#include "runtime/core/base/core.h"
#include "runtime/function/physics/collision_shape2d.h"
#include <SimpleMath.h>

namespace Toy2D {
    class Physics2DManager {
    public:
        Physics2DManager();
        void        resetWorld();
        b2Body* createBody(int entity_id, float x, float y, float rotation, bool is_dynamic, bool is_kinematic, CollisionShape2D& shape2d);
        ~Physics2DManager();
        using Transform2D = std::tuple<float, float, float>;
        Transform2D getTransform(void* runtime_body);
        Transform2D getVelocity(void* runtime_body);
        void        setVelocity(void* runtime_body, float v_x, float v_y, float v_r);
        void        update();

    private:
        Scope<b2World> m_world;
        
        static Physics2DManager* s_physics2d_manager;
    };
} // namespace Toy2D
