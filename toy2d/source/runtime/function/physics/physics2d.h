#pragma once

#include "runtime/function/physics/collider2d.h"

namespace Toy2D {
    class Physics2DManager {
    public:
        Physics2DManager();
        void        resetWorld();
        b2Body*     createBody(EntityIdType entity_id, float x, float y, float rotation, bool is_dynamic, bool is_kinematic, bool fixed_rotaion, Collider2D& collider);
        
        struct BodyDef {
            EntityIdType entity_id;
            float        x;
            float        y;
            float        rotation;
            bool         is_dynamic;
            bool         is_kinematic;
            bool         fixed_rotaion;
            Collider2D*  collider;
        };
        b2Body*     createBody(BodyDef& bodydef);
        ~Physics2DManager();
        
        using Transform2D = std::tuple<float, float, float>;
        Transform2D getTransform(void* runtime_body);
        Transform2D getVelocity(void* runtime_body);
        void        setVelocity(void* runtime_body, float v_x, float v_y, float v_r);
        void        update();

    private:
        Scope<b2World> m_world;
        Scope<ContactListener2D> m_contact_listener;
    };
} // namespace Toy2D
