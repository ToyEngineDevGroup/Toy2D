#include "runtime/function/physics/physics2d.h"
#include <runtime/core/log/log_system.h>

Toy2D::Physics2DManager* Toy2D::Physics2DManager::s_physics2d_manager{nullptr};

Toy2D::Physics2DManager::Physics2DManager() {
    resetWorld();
}

void Toy2D::Physics2DManager::resetWorld() {
    b2Vec2 gravity(0.0f, -9.8f);
    m_world = CreateScope<b2World>(gravity);
}

b2Body* Toy2D::Physics2DManager::createBody(int entity_id, float x, float y, float rotation, bool is_dynamic, bool is_kinematic, CollisionShape2D* shape2d) {
    b2BodyDef body_def{};
    body_def.position.Set(x, y);
    body_def.angle = rotation;
    b2FixtureDef fixture_def{};
    ASSERT(shape2d != nullptr, "You should create a shape for a rigidbody!");
    if (shape2d == nullptr) {
        return nullptr;
    }		
    fixture_def.shape = shape2d->m_b2shape.get();
    if (is_dynamic) {
        body_def.type = b2_dynamicBody;
        fixture_def.density = 1.0f;
        fixture_def.friction = 0.3f;
    }
    else if (is_kinematic) {
        body_def.type = b2_kinematicBody;
    }
    else {
        body_def.type = b2_staticBody;
    }

    b2Body* body = m_world->CreateBody(&body_def);
    body->CreateFixture(&fixture_def);

    LOG_INFO("creating body for entity#{}, type={} at ({}, {}), rotation = {}", entity_id, body_def.type, body->GetPosition().x, body->GetPosition().y, body->GetAngle());
        
    return body;
}

Toy2D::Physics2DManager::~Physics2DManager() {

}

Toy2D::Physics2DManager::Transform2D Toy2D::Physics2DManager::getTransform(void* runtime_body) {
    b2Body* body = reinterpret_cast<b2Body*>(runtime_body);
    if (!body) {
        return Transform2D(0.0f, 0.0f, 0.0f);
    }
    return Transform2D(body->GetPosition().x, body->GetPosition().y, body->GetAngle());
}

Toy2D::Physics2DManager::Transform2D Toy2D::Physics2DManager::getVelocity(void* runtime_body) {
    b2Body* body = reinterpret_cast<b2Body*>(runtime_body);
    return Transform2D(body->GetLinearVelocity().x, body->GetLinearVelocity().y, body->GetAngularVelocity());
}

void Toy2D::Physics2DManager::setVelocity(void* runtime_body, float v_x, float v_y, float v_r) {
    b2Body* body = reinterpret_cast<b2Body*>(runtime_body);
    body->SetLinearVelocity(b2Vec2(v_x, v_y));
    body->SetAngularVelocity(v_r);
}

void Toy2D::Physics2DManager::update() {
    m_world->Step(0.001, 1, 1);
}




