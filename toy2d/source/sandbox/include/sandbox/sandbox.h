#pragma once

#include "sandbox/example_layer.h"

class Sandbox : public Toy2D::Application {
public:
    Sandbox() {
        pushLayer(new ExampleLayer());
    }

    ~Sandbox() {
    }
};

Toy2D::Application* createApp() {
    return new Sandbox();
}
