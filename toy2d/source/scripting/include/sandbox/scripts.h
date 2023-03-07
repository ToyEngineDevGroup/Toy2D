#pragma once

#include "runtime/toy2d.h"
extern int* g_player_money;
class CameraController : public Toy2D::ScriptableEntity {
public:
    void onCreate() override {
    }

    void onDestroy() override {
    }

    void onUpdate(Toy2D::TimeStep timestep) override {
        auto& transform = getComponent<Toy2D::TransformComponent>();
        float speed     = 3.0f;

        if (Toy2D::InputSystem::isKeyPressed('A'))
            transform.translation.x -= speed * timestep;
        if (Toy2D::InputSystem::isKeyPressed('D'))
            transform.translation.x += speed * timestep;
        if (Toy2D::InputSystem::isKeyPressed('W'))
            transform.translation.y += speed * timestep;
        if (Toy2D::InputSystem::isKeyPressed('S'))
            transform.translation.y -= speed * timestep;
    }
};

class PlayerController : public Toy2D::ScriptableEntity {
public:
    void onCreate() override {
        g_player_money = &money;
    }

    void onDestroy() override {
    }

    void onUpdate(Toy2D::TimeStep timestep) override {
        auto& rigidbody2d = getComponent<Toy2D::Rigidbody2DComponent>();
        float speed       = 1.0f;

        // if (Toy2D::InputSystem::isKeyPressed('A'))
        //     rigidbody2d.linear_velocity.x = -speed;
        // if (Toy2D::InputSystem::isKeyPressed('D'))
        //     rigidbody2d.linear_velocity.x = speed;
        // if (Toy2D::InputSystem::isKeyPressed('W'))
        //     rigidbody2d.linear_velocity.y = speed;
        // if (Toy2D::InputSystem::isKeyPressed('S'))
        //     rigidbody2d.linear_velocity.y = -speed;
    }

    int money{0};

    void onCollisionEnter(Toy2D::Entity entity) override {
        if (entity.hasComponent<Toy2D::NameComponent>() && entity.hasComponent<Toy2D::TransformComponent>()) {
            if (entity.getComponent<Toy2D::NameComponent>().name.starts_with("money_")) {
                money = money + 1;
                LOG_INFO("You got $1! Now you have ${}", money);
                entity.getComponent<Toy2D::TransformComponent>().translation.y = -100.0f;
            }
        }
    }

    void onCollisionExit(Toy2D::Entity entity) override {
    }
};

class AnimeScript : public Toy2D::ScriptableEntity {
    void onCreate() override {
    }

    void onDestroy() override {
    }

    void onUpdate(Toy2D::TimeStep timestep) override {
        static int bias = 18;

        if (Toy2D::InputSystem::isKeyPressed('W'))
            bias = 6;
        if (Toy2D::InputSystem::isKeyPressed('S'))
            bias = 18;
        if (Toy2D::InputSystem::isKeyPressed('D'))
            bias = 0;
        if (Toy2D::InputSystem::isKeyPressed('A'))
            bias = 12;

        static uint32_t x_pos        = 0;
        static float    elapsed_time = 0.0f;
        elapsed_time += timestep;
        if (elapsed_time >= 0.1f) {
            auto& tile   = getComponent<Toy2D::TileComponent>();
            tile.coord_x = ((tile.coord_x + 1) % 6) + bias;
            elapsed_time -= 0.1f;
        }
    }
};