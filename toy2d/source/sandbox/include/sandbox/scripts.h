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
    }

    void onDestroy() override {
    }

    void onUpdate(Toy2D::TimeStep timestep) override {
        auto& rigidbody2d = getComponent<Toy2D::Rigidbody2DComponent>();
        float speed     = 3.0f;

        if (Toy2D::InputSystem::isKeyPressed('A'))
            rigidbody2d.setVelocity(-2.5f, 0.0f);
        if (Toy2D::InputSystem::isKeyPressed('D'))
            rigidbody2d.setVelocity(2.5f, 0.0f);
        if (Toy2D::InputSystem::isKeyPressed('W'))
            rigidbody2d.setVelocity(0.0f, 2.5f);
        if (Toy2D::InputSystem::isKeyPressed('S'))
            rigidbody2d.setVelocity(0.0f, -2.5f);
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
