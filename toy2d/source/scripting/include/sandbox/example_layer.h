#pragma once

#include "runtime/toy2d.h"

class ExampleLayer : public Toy2D::Layer {
public:
    ExampleLayer() :
        Layer("Example") {
    }

    void onAttach() override;
    void onDetach() override;
    void onUpdate(Toy2D::TimeStep timestep) override;
    void onImGuiRender() override;
    void onEvent(Toy2D::Event& event) override;
    bool onWindowResizeEvent(Toy2D::WindowResizeEvent& event);

private:
    Toy2D::World m_world;
};