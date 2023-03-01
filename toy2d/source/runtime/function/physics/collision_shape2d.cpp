#include "runtime/function/physics/collision_shape2d.h"

Toy2D::CollisionShape2D::CollisionShape2D() {
}

Toy2D::CollisionShape2D* Toy2D::CollisionShape2D::createBox(float w, float h) {
    CollisionShape2D* shape = new CollisionShape2D;
    Scope<b2PolygonShape> b2shape        = CreateScope<b2PolygonShape>();
    b2shape->SetAsBox(w/2, h/2);
    shape->m_b2shape = std::move(b2shape);
    return shape;
}
