#include "runtime/function/physics/physics2d.h"

namespace Toy2D {

    Physics2DManager::Physics2DManager() {
        resetWorld();
    }

    void Physics2DManager::resetWorld() {
        b2Vec2 gravity(0.0f, -9.8f);
        m_world = CreateScope<b2World>(gravity);
        m_contact_listener = CreateScope<ContactListener2D>();
        m_world->SetContactListener(m_contact_listener.get());
    }

    b2Body* Physics2DManager::createBody(EntityIdType entity_id, float x, float y, float rotation, bool is_dynamic, bool is_kinematic, bool fixed_rotation, Collider2D& collider) {
        BodyDef bodydef;
        bodydef.entity_id = entity_id;
        bodydef.x         = x;
        bodydef.y         = y;
        bodydef.rotation  = rotation;
        bodydef.is_dynamic = is_dynamic;
        bodydef.is_kinematic = is_kinematic;
        bodydef.fixed_rotaion = fixed_rotation;
        bodydef.collider      = &collider;
        return createBody(bodydef);
    }    
    b2Body* Physics2DManager::createBody(BodyDef& bodydef) {    
        b2BodyDef b2_bodydef{};
        b2_bodydef.position.Set(bodydef.x, bodydef.y);
        b2_bodydef.angle               = bodydef.rotation;
        b2_bodydef.userData.pointer = reinterpret_cast<uintptr_t>(bodydef.collider);
        b2_bodydef.fixedRotation       = bodydef.fixed_rotaion;
        bodydef.collider->m_entity_id = bodydef.entity_id;
        b2FixtureDef b2_fixturedef{};
        ASSERT(bodydef.collider->m_b2shape.get() != nullptr, "You should create a shape for a rigidbody!");
        if (bodydef.collider->m_b2shape.get() == nullptr) {
            return nullptr;
        }
        b2_fixturedef.shape = bodydef.collider->m_b2shape.get();
        if (bodydef.is_dynamic) {
            b2_bodydef.type        = b2_dynamicBody;
            b2_fixturedef.density  = 1.0f;
            b2_fixturedef.friction = 0.3f;
        }
        else if (bodydef.is_kinematic) {
            b2_bodydef.type = b2_kinematicBody;
        }
        else {
            b2_bodydef.type = b2_staticBody;
        }

        b2Body* body = m_world->CreateBody(&b2_bodydef);
        body->CreateFixture(&b2_fixturedef);

        LOG_INFO("creating body for entity#{}, type={} at ({}, {}), rotation = {}", bodydef.entity_id, b2_bodydef.type, body->GetPosition().x, body->GetPosition().y, body->GetAngle());

        return body;
    }

    Physics2DManager::~Physics2DManager() {
    }

    Physics2DManager::Transform2D Physics2DManager::getTransform(void* runtime_body) {
        b2Body* body = reinterpret_cast<b2Body*>(runtime_body);
        if (!body) {
            return Transform2D(0.0f, 0.0f, 0.0f);
        }
        return Transform2D(body->GetPosition().x, body->GetPosition().y, body->GetAngle());
    }

    Physics2DManager::Transform2D Physics2DManager::getVelocity(void* runtime_body) {
        b2Body* body = reinterpret_cast<b2Body*>(runtime_body);
        return Transform2D(body->GetLinearVelocity().x, body->GetLinearVelocity().y, body->GetAngularVelocity());
    }

    void Physics2DManager::setVelocity(void* runtime_body, float v_x, float v_y, float v_r) {
        b2Body* body = reinterpret_cast<b2Body*>(runtime_body);
        body->SetLinearVelocity(b2Vec2(v_x, v_y));
        body->SetAngularVelocity(v_r);
    }

    void Physics2DManager::update() {
        m_world->Step(0.001, 1, 1);
    }

}


