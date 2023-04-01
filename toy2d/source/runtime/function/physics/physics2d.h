#pragma once

#include "runtime/function/physics/collider2d.h"

namespace Toy2D {
    class Physics2DManager {
    public:
        Physics2DManager();

        void setGravity(const Vector2& g) {
            m_gravity = g;
            resetWorld();
        }

        void resetWorld();

        struct BodyDef {
            EntityIdType entity_id;
            float        x;
            float        y;
            float        rotation;
            bool         is_dynamic;
            bool         is_kinematic;
            bool         fixed_rotaion;
            unsigned int mask_bits;
            unsigned int category_bits;
            Collider2D*  collider;
        };
        void* createBody(BodyDef& bodydef);
        void  deleteBody(void* runtime_body);
        ~Physics2DManager();

        using Transform2D = std::tuple<float, float, float>;
        Transform2D getTransform(void* runtime_body);
        void        setTransform(void* runtime_body, float x, float y, float r);
        Transform2D getVelocity(void* runtime_body);
        void        setVelocity(void* runtime_body, float v_x, float v_y, float v_r);
        void        update(float timestep);

    private:
        Scope<b2World>           m_world;
        Scope<ContactListener2D> m_contact_listener;
        Scope<ContactFilter2D>   m_contact_filter;

        Vector2 m_gravity;
    };
} // namespace Toy2D
