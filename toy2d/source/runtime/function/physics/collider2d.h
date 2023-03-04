#pragma once

namespace Toy2D{
    class Physics2DManager;
    class ContactListener2D;
    class Collider2D {
    public:
        friend class Physics2DManager;
        friend class ContactListener2D;
        Collider2D();
        void createBox(float w, float h);
        
        float getBoxWidth();
        float getBoxHeight();

        EntityIdType getEntity();
        bool         hasCollisionEnterEvent();
        EntityIdType getCollisionEnterEvent();
        bool         hasCollisionExitEvent();
        EntityIdType getCollisionExitEvent();

        bool         stayWith(EntityIdType e);
        bool         is_one_sided_collision{false};
        bool         is_trigger{false};

    private:
        Scope<b2Shape> m_b2shape;
        EntityIdType           m_entity_id{0};
        std::set<EntityIdType> m_collision_enter_event;
        std::set<EntityIdType> m_collision_exit_event;
        std::set<EntityIdType> m_collision_stay_event;
        union {
            struct {
                float w, h;
            } rect;
            struct {
                float r;
            } circle;
        } m_size{};
    };

    class ContactListener2D : public b2ContactListener {
    public:
        void BeginContact(b2Contact* contact) {
            Collider2D* colliderA = (Collider2D*)contact->GetFixtureA()->GetBody()->GetUserData().pointer;
            Collider2D* colliderB = (Collider2D*)contact->GetFixtureB()->GetBody()->GetUserData().pointer;
            colliderA->m_collision_enter_event.insert(colliderB->getEntity());
            colliderB->m_collision_enter_event.insert(colliderA->getEntity());
        }
        void EndContact(b2Contact* contact) {
            Collider2D* colliderA = (Collider2D*)contact->GetFixtureA()->GetBody()->GetUserData().pointer;
            Collider2D* colliderB = (Collider2D*)contact->GetFixtureB()->GetBody()->GetUserData().pointer;
            colliderA->m_collision_exit_event.insert(colliderB->getEntity());
            colliderB->m_collision_exit_event.insert(colliderA->getEntity());
        }
        void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
            Collider2D* colliderA = (Collider2D*)contact->GetFixtureA()->GetBody()->GetUserData().pointer;
            Collider2D* colliderB = (Collider2D*)contact->GetFixtureB()->GetBody()->GetUserData().pointer;
            if ((colliderA->is_trigger || colliderB->is_trigger)) {
                if (!colliderA->stayWith(colliderB->getEntity())) {
                    colliderA->m_collision_enter_event.insert(colliderB->getEntity());
                    colliderB->m_collision_enter_event.insert(colliderA->getEntity());
                }
                contact->SetEnabled(false);
            }
        }
        void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {
        }
    };
}; // namespace Toy2D
