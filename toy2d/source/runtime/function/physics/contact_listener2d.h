#pragma once
#include <box2d/box2d.h> // 去掉这一行就会报错，暂时解决不了，该文件的其他设置都与别的文件相同但是无法默认使用预编译头
#include "runtime/function/physics/collider2d.h"

namespace Toy2D {
    class ContactListener2D : public b2ContactListener {
    public:
        void BeginContact(b2Contact* contact) {
            Collider2D* colliderA = (Collider2D*)contact->GetFixtureA()->GetBody()->GetUserData().pointer;
            Collider2D* colliderB = (Collider2D*)contact->GetFixtureB()->GetBody()->GetUserData().pointer;
            colliderA;
        }
        void EndContact(b2Contact* contact) {

        }
        void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {

        }
        void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {

        }
    };
};
