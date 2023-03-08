#include "sandbox/example_layer.h"
#include "sandbox/scripts.h"

int* g_player_money = nullptr;

void ExampleLayer::onAttach() {
    LOG_TRACE("attach");

    Toy2D::Application::get().getResourceMngr()->add<Toy2D::ResourceType::TileSheet>(
        Toy2D::Application::get().getConfigMngr()->getAssetFolder() / "desc/tilesheet/player.json");
    Toy2D::Application::get().getResourceMngr()->add<Toy2D::ResourceType::Texture>(
        Toy2D::Application::get().getConfigMngr()->getAssetFolder() / "desc/tex/asoul_desc.json");
    Toy2D::Application::get().getResourceMngr()->add<Toy2D::ResourceType::Texture>(
        Toy2D::Application::get().getConfigMngr()->getAssetFolder() / "desc/tex/bella_desc.json");
    Toy2D::Application::get().getResourceMngr()->add<Toy2D::ResourceType::Texture>(
        Toy2D::Application::get().getConfigMngr()->getAssetFolder() / "desc/tex/box_desc.json");
    Toy2D::Application::get().getResourceMngr()->add<Toy2D::ResourceType::Texture>(
        Toy2D::Application::get().getConfigMngr()->getAssetFolder() / "desc/tex/money_desc.json");

    m_world.addScene("main").setActiveScene("main").onResize(
        Toy2D::Application::get().getWindow()->getWidth(),
        Toy2D::Application::get().getWindow()->getHeight());

    auto&& player = m_world.getActiveScene()->createEntity("player");
    player.addComponent<Toy2D::CameraComponent>().camera.setOrthographicSize(5.0f);
    player.addComponent<Toy2D::TileComponent>("player");
    {
        auto& transform = player.getComponent<Toy2D::TransformComponent>();
    }
    player.addComponent<Toy2D::NativeScriptComponent>().bind<PlayerController>();
    {
        auto& rigidbody             = player.addComponent<Toy2D::Rigidbody2DComponent>();
        rigidbody.type              = Toy2D::Rigidbody2DComponent::BodyType::Dynamic;
        rigidbody.is_fixed_rotation = true;
        rigidbody.collider.createBox(0.5f, 0.5f);
    }

    auto&& square = m_world.getActiveScene()->createEntity("square");
    square.addComponent<Toy2D::SpriteComponent>();
    square.addComponent<Toy2D::Rigidbody2DComponent>().collider.createBox(1.0f, 1.0f);
    {
        auto& transform         = square.getComponent<Toy2D::TransformComponent>();
        transform.translation.y = -1.5f;
        transform.rotation.z    = 0.3f;
    }

    auto&& another_square = m_world.getActiveScene()->createEntity("another_square");
    another_square.addComponent<Toy2D::SpriteComponent>();
    another_square.addComponent<Toy2D::Rigidbody2DComponent>().collider.createBox(1.0f, 1.0f);
    {
        auto& transform         = another_square.getComponent<Toy2D::TransformComponent>();
        transform.translation.y = -1.5f;
        transform.translation.x = -1.0f;
        transform.rotation.z    = 0.3f;
    }

    int  money_count = 0;
    auto addMoney    = [=](float x, float y) {
        auto&& money = m_world.getActiveScene()->createEntity(std::format("money_{}", money_count));
        {
            auto& sprite     = money.addComponent<Toy2D::SpriteComponent>();
            sprite.tex_index = Toy2D::Application::get().getResourceMngr()->index<Toy2D::ResourceType::Texture>("money");
        }
        {
            auto& rigidbody               = money.addComponent<Toy2D::Rigidbody2DComponent>();
            rigidbody.is_fixed_rotation   = true;
            rigidbody.collider.is_trigger = true;
            rigidbody.collider.createBox(0.1f, 0.1f);
        }
        {
            auto& transform         = money.getComponent<Toy2D::TransformComponent>();
            transform.translation.x = x;
            transform.translation.y = y;
            transform.scale.x       = 0.1;
            transform.scale.y       = 0.1;
        }
    };

    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j)
            addMoney(i * 0.2 - 1.0, j * 0.2);

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

    if (g_player_money)
        Toy2D::Widgets::drawText(std::format("Move with W,A,S,D. Have a try!!! [ Your money: {} ]", *g_player_money));
}

void ExampleLayer::onEvent(Toy2D::Event& event) {
    Toy2D::EventDispatcher dispatcher(event);
    dispatcher.Dispatch<Toy2D::WindowResizeEvent>(BIND_EVENT_FN(ExampleLayer::onWindowResizeEvent));
}

bool ExampleLayer::onWindowResizeEvent(Toy2D::WindowResizeEvent& event) {
    m_world.onResize(event.getWidth(), event.getHeight());

    return false;
}
