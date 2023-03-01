// Box2D
#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_world.h>

#include "runtime/function/render/render_system/renderer_2d.h"
#include "runtime/function/scene/components.h"
#include "runtime/function/scene/entity.h"
#include "runtime/function/scene/scene.h"

namespace Toy2D {
    Scene::~Scene() {
    }

    Entity Scene::createEntity(const std::string& name) {
        static uint32_t create_entity_count = 0;

        Entity entity = {m_registry.create(), this};
        entity.addComponent<TransformComponent>();
        auto& name_component = entity.addComponent<NameComponent>();
        name_component.name  = (name.empty()) ? ("Entity" + std::to_string(create_entity_count)) :
                                                name;

        create_entity_count++;

        return entity;
    }

    void Scene::destroyEntity(Entity entity) {
        m_registry.destroy(entity);
    }

    void Scene::onRuntimeStart() {
        m_physics2d_manager = CreateScope<Physics2DManager>();
    }

    void Scene::onRuntimeStop() {
        m_physics2d_manager.reset();
    }

    void Scene::onUpdateRuntime(TimeStep timestep) {
        // update scripts
        {
            m_registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc) {
                if (!nsc.instance) {
                    nsc.instance           = nsc.instantiateScript();
                    nsc.instance->m_entity = Entity{entity, this};
                    nsc.instance->onCreate();
                }

                nsc.instance->onUpdate(timestep);
            });
        }

        // render
        SceneCamera* curr_camera = nullptr;
        Matrix       camera_transform{Matrix::Identity};
        {
            auto view = m_registry.view<TransformComponent, CameraComponent>();
            for (auto entity : view) {
                auto [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);
                TransformComponent transform_cam;
                transform_cam.translation = transform.translation;
                transform_cam.scale       = transform.scale;
                if (camera.is_current) {
                    curr_camera      = &camera.camera;
                    camera_transform = transform_cam.getTransform();
                    break;
                }
            }
        }

        if (curr_camera) {
            Renderer2D::beginScene(*curr_camera, camera_transform);

            auto group = m_registry.group<TransformComponent>(entt::get<SpriteComponent>);
            for (auto entity : group) {
                auto [transform, sprite] = group.get<TransformComponent, SpriteComponent>(entity);

                Renderer2D::drawSprite(transform.getTransform(), sprite, (int)entity);
            }
        }

        Renderer2D::endScene();

        for (auto entity : m_submit_body_creation) {
            bool is_dynamic = false, is_kinematic = false;
            auto& rigidbody2d = m_registry.get<Rigidbody2DComponent>(entity);
            auto& transform = m_registry.get<TransformComponent>(entity);
            switch (rigidbody2d.type) {
                case Rigidbody2DComponent::BodyType::Dynamic:
                    is_dynamic = true;
                    break;
                case Rigidbody2DComponent::BodyType::Kinematic:
                    is_kinematic = true;
                    break;
            }
            rigidbody2d.runtime_body = reinterpret_cast<void*>(m_physics2d_manager->createBody((int)entity, transform.translation.x, transform.translation.y, transform.rotation.z, is_dynamic, is_kinematic, rigidbody2d.shape));
        }
        m_submit_body_creation.clear();

        auto rigidbody2d_view = m_registry.view<TransformComponent, Rigidbody2DComponent>();
        for (auto entity : rigidbody2d_view) {
            auto& transform = m_registry.get<TransformComponent>(entity);
            auto& rigidbody = m_registry.get<Rigidbody2DComponent>(entity);
            std::tie(transform.translation.x, transform.translation.y, transform.rotation.z) = m_physics2d_manager->getTransform(rigidbody.runtime_body);
            if (rigidbody.submit_velocity_change) {
                rigidbody.submit_velocity_change = false;
                m_physics2d_manager->setVelocity(rigidbody.runtime_body, rigidbody.velocity.x, rigidbody.velocity.y, rigidbody.a_velocity);
            }
            std::tie(rigidbody.velocity.x, rigidbody.velocity.y, rigidbody.a_velocity) = m_physics2d_manager->getVelocity(rigidbody.runtime_body);
        }

        m_physics2d_manager->update();

    }

    void Scene::onUpdateEditor(TimeStep timestep, EditorCamera& camera) {
        Renderer2D::beginScene(camera);

        auto group = m_registry.group<TransformComponent>(entt::get<SpriteComponent>);
        for (auto entity : group) {
            auto [transform, sprite] = group.get<TransformComponent, SpriteComponent>(entity);

            Renderer2D::drawSprite(transform.getTransform(), sprite, (int)entity);
        }

        Renderer2D::endScene();
    }

    void Scene::onViewportResize(uint32_t width, uint32_t height) {
        m_viewport_width  = width;
        m_viewport_height = height;

        // resize non-fixedAspectRatio cameras
        auto view = m_registry.view<CameraComponent>();
        for (auto& entity : view) {
            auto& camera_component = view.get<CameraComponent>(entity);
            if (!camera_component.is_fixed_aspectRatio) {
                camera_component.camera.setViewportSize(width, height);
            }
        }
    }

    Entity Scene::getPrimaryCameraEntity() {
        auto view = m_registry.view<CameraComponent>();
        for (auto entity : view) {
            const auto& camera = view.get<CameraComponent>(entity);
            if (camera.is_current)
                return Entity{entity, this};
        }
        return {};
    }

    template <typename T>
    void Scene::onComponentAdded(Entity entity, T& component) {
        // static_assert(false);
    }

    template <>
    void Scene::onComponentAdded<TransformComponent>(Entity entity, TransformComponent& component) {
    }

    template <>
    void Scene::onComponentAdded<CameraComponent>(Entity entity, CameraComponent& component) {
        component.camera.setViewportSize(m_viewport_width, m_viewport_height);
    }

    template <>
    void Scene::onComponentAdded<SpriteComponent>(Entity entity, SpriteComponent& component) {
    }

    template <>
    void Scene::onComponentAdded<NameComponent>(Entity entity, NameComponent& component) {
    }

    template <>
    void Scene::onComponentAdded<NativeScriptComponent>(Entity entity, NativeScriptComponent& component) {
    }

    template <>
    void Scene::onComponentAdded<Rigidbody2DComponent>(Entity entity, Rigidbody2DComponent& component) {
        m_submit_body_creation.push_back(entity);
    }

} // namespace Toy2D