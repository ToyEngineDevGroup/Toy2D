#pragma once

#include "runtime/toy2d.h"
class CameraController : public Toy2D::ScriptableEntity {
public:
    void onCreate() override {
    }

    void onDestroy() override {
    }

    void onUpdate(Toy2D::TimeStep timestep) override {
        auto& transform = getComponent<Toy2D::TransformComponent>();
        float speed     = 3.0f;

        // if (Toy2D::InputSystem::isKeyPressed('A'))
        //     transform.translation.x -= speed * timestep;
        // if (Toy2D::InputSystem::isKeyPressed('D'))
        //     transform.translation.x += speed * timestep;
        // if (Toy2D::InputSystem::isKeyPressed('W'))
        //     transform.translation.y += speed * timestep;
        // if (Toy2D::InputSystem::isKeyPressed('S'))
        //     transform.translation.y -= speed * timestep;
    }
};

class AnimeScript : public Toy2D::ScriptableEntity {
    void onCreate() override {
    }

    void onDestroy() override {
    }

    void onUpdate(Toy2D::TimeStep timestep) override {
        auto& transform = getComponent<Toy2D::TransformComponent>();
        float speed     = 1.0f;

        if (Toy2D::InputSystem::isKeyPressed('A'))
            transform.translation.x -= speed * timestep;
        if (Toy2D::InputSystem::isKeyPressed('D'))
            transform.translation.x += speed * timestep;
        if (Toy2D::InputSystem::isKeyPressed('W'))
            transform.translation.y += speed * timestep;
        if (Toy2D::InputSystem::isKeyPressed('S'))
            transform.translation.y -= speed * timestep;

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