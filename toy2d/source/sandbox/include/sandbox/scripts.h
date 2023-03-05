#pragma once

#include "runtime/toy2d.h"

class CameraController : public Toy2D::ScriptableEntity {
public:
    void onCreate() override {
    }

    void onDestroy() override {
    }

    void onUpdate(Toy2D::TimeStep timestep) override {
        auto& transform = getComponent<Toy2D::TransformComponent>().translation;
        float speed     = 3.0f;

        if (Toy2D::InputSystem::isKeyPressed('A'))
            transform.x -= speed * timestep;
        if (Toy2D::InputSystem::isKeyPressed('D'))
            transform.x += speed * timestep;
        if (Toy2D::InputSystem::isKeyPressed('W'))
            transform.y += speed * timestep;
        if (Toy2D::InputSystem::isKeyPressed('S'))
            transform.y -= speed * timestep;
    }
};

class TexMarchingScript : public Toy2D::ScriptableEntity {
public:
    void onCreate() override {
    }

    void onDestroy() override {
    }

    void onUpdate(Toy2D::TimeStep timestep) override {
        static float elapsed_time = 0.0f;
        elapsed_time += timestep;
        if (elapsed_time >= 1.0f) {
            auto& sprite = getComponent<Toy2D::SpriteComponent>();
            sprite.tex_index =
                (sprite.tex_index + 1) % Toy2D::Application::get().getResourceMngr()->size<Toy2D::ResourceType::Texture>();
            elapsed_time -= 1.0f;
        }
    }
};

class AnimeScript : public Toy2D::ScriptableEntity {
    void onCreate() override {
    }

    void onDestroy() override {
    }

    void onUpdate(Toy2D::TimeStep timestep) override {
        static uint32_t x_pos        = 0;
        static float    elapsed_time = 0.0f;
        elapsed_time += timestep;
        if (elapsed_time >= 0.1f) {
            auto& tile   = getComponent<Toy2D::TileComponent>();
            tile.coord_x = (tile.coord_x + 1) % 6;
            elapsed_time -= 0.1f;
        }
    }
};