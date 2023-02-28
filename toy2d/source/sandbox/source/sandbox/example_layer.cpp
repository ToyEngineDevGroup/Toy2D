#include "sandbox/example_layer.h"
#include "sandbox/scripts.h"

void ExampleLayer::onAttach() {
    LOG_TRACE("attach");

    Toy2D::Application::get().getResourceMngr()->add<Toy2D::ResourceType::Texture>(
        Toy2D::Application::get().getConfigMngr()->getAssetFolder() / "texture/asoul_moon.png");
    Toy2D::Application::get().getResourceMngr()->add<Toy2D::ResourceType::Texture>(
        Toy2D::Application::get().getConfigMngr()->getAssetFolder() / "texture/bella.png");

    m_world.addScene("main").setActiveScene("main").onResize(
        Toy2D::Application::get().getWindow()->getWidth(),
        Toy2D::Application::get().getWindow()->getHeight());

    auto&& player = m_world.getActiveScene()->createEntity("player");
    player.addComponent<Toy2D::CameraComponent>().camera.setOrthographicSize(5.0f);
    player.addComponent<Toy2D::SpriteComponent>().tex_index =
        Toy2D::Application::get().getResourceMngr()->index<Toy2D::ResourceType::Texture>("bella");
    player.addComponent<Toy2D::NativeScriptComponent>().bind<CameraController>();

    auto&& square = m_world.getActiveScene()->createEntity("square");
    square.addComponent<Toy2D::SpriteComponent>();
    square.addComponent<Toy2D::NativeScriptComponent>().bind<TexMarchingScript>();

    // Toy2D::SceneSerializer serializer(m_world.getActiveScene());
    // serializer.deserialize(Toy2D::Application::get().getConfigMngr()->getAssetFolder() / "scene/scene.json");
}

void ExampleLayer::onDetach() {
    LOG_TRACE("detach");
}

void ExampleLayer::onUpdate(Toy2D::TimeStep timestep) {
    m_world.onUpdateRuntime(timestep);
}

void ExampleLayer::onImGuiRender() {
    Toy2D::Widgets::drawButton(
        "Button",
        Vector2{200.0f, 100.0f},
        Color{0.5f, 0.5f, 0.5f, 0.8f},
        Color{0.8f, 0.8f, 0.8f, 1.0f},
        Color{0.4f, 0.4f, 0.4f, 1.0f},
        []() {
        LOG_INFO("Button Clicked");
        });

    Toy2D::Widgets::drawText("Hello world");
}

void ExampleLayer::onEvent(Toy2D::Event& event) {
    Toy2D::EventDispatcher dispatcher(event);
    dispatcher.Dispatch<Toy2D::WindowResizeEvent>(BIND_EVENT_FN(ExampleLayer::onWindowResizeEvent));
}

bool ExampleLayer::onWindowResizeEvent(Toy2D::WindowResizeEvent& event) {
    m_world.onResize(event.getWidth(), event.getHeight());

    return false;
}
