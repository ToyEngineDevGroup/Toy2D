#pragma once
#include <box2d/box2d.h> // ȥ����һ�оͻᱨ����ʱ������ˣ����ļ����������ö������ļ���ͬ�����޷�Ĭ��ʹ��Ԥ����ͷ
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
