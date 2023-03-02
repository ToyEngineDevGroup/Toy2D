#include "sandbox/example_layer.h"
#include "sandbox/scripts.h"

void ExampleLayer::onAttach() {
    LOG_TRACE("attach");

    Toy2D::Application::get().getResourceMngr()->add<Toy2D::ResourceType::TileSheet>(
        Toy2D::Application::get().getConfigMngr()->getAssetFolder() / "desc/tilesheet/tilesheet.json");
    Toy2D::Application::get().getResourceMngr()->add<Toy2D::ResourceType::Texture>(
        Toy2D::Application::get().getConfigMngr()->getAssetFolder() / "desc/tex/asoul_desc.json");
    Toy2D::Application::get().getResourceMngr()->add<Toy2D::ResourceType::Texture>(
        Toy2D::Application::get().getConfigMngr()->getAssetFolder() / "desc/tex/bella_desc.json");

    m_world.addScene("main").setActiveScene("main").onResize(
        Toy2D::Application::get().getWindow()->getWidth(),
        Toy2D::Application::get().getWindow()->getHeight());

    auto&& player = m_world.getActiveScene()->createEntity("player");
    player.addComponent<Toy2D::CameraComponent>().camera.setOrthographicSize(5.0f);
    player.addComponent<Toy2D::SpriteComponent>().tex_index =
        Toy2D::Application::get().getResourceMngr()->index<Toy2D::ResourceType::Texture>("bella");
    player.addComponent<Toy2D::NativeScriptComponent>().bind<PlayerController>();
    auto& rigidbody = player.addComponent<Toy2D::Rigidbody2DComponent>();
    rigidbody.type   = Toy2D::Rigidbody2DComponent::BodyType::Dynamic;
    rigidbody.setAsRectange(0.5f, 0.5f);

    auto&& square = m_world.getActiveScene()->createEntity("square");
    square.addComponent<Toy2D::SpriteComponent>();
    square.addComponent<Toy2D::NativeScriptComponent>().bind<TexMarchingScript>();
    square.addComponent<Toy2D::Rigidbody2DComponent>().setAsRectange(1.0f, 1.0f);
    auto& transform = square.getComponent<Toy2D::TransformComponent>();
    transform.translation.y = -1.5f;
    transform.rotation.z    = 0.3f;

    auto&& tile = m_world.getActiveScene()->createEntity("tile");
    tile.addComponent<Toy2D::TileComponent>(
        Toy2D::Application::get().getResourceMngr()->get<Toy2D::ResourceType::TileSheet>("tilesheet"),
        Vector2{0, 3});
    tile.getComponent<Toy2D::TransformComponent>().translation.x += 3.0f;

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

    Toy2D::Widgets::drawText("Move with W,A,S,D. Have a try!!!");
}

void ExampleLayer::onEvent(Toy2D::Event& event) {
    Toy2D::EventDispatcher dispatcher(event);
    dispatcher.Dispatch<Toy2D::WindowResizeEvent>(BIND_EVENT_FN(ExampleLayer::onWindowResizeEvent));
}

bool ExampleLayer::onWindowResizeEvent(Toy2D::WindowResizeEvent& event) {
    m_world.onResize(event.getWidth(), event.getHeight());

    return false;
}
