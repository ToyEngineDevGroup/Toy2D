#include "runtime/function/physics/collision_shape2d.h"

Toy2D::CollisionShape2D::CollisionShape2D() {
}

void Toy2D::CollisionShape2D::createBox(float w, float h) {
    Scope<b2PolygonShape> b2shape        = CreateScope<b2PolygonShape>();
    b2shape->SetAsBox(w/2, h/2);
    m_b2shape = std::move(b2shape);
}
