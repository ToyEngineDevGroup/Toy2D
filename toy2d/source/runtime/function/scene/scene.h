#pragma once

#include <entt/entt.hpp>

#include "runtime/core/util/time_step.h"
#include "runtime/function/render/camera_system/editor_camera.h"
#include <runtime/function/physics/physics2d.h>

class b2World;

namespace Toy2D {
    class Entity;
    class SceneHierarchyPanel;
    class SceneSerializer;

    class Scene {
        friend class Entity;
        friend class SceneHierarchyPanel;
        friend class SceneSerializer;

    public:
        Scene() = default;
        ~Scene();

        Entity createEntity(const std::string& name = std::string{});
        void   destroyEntity(Entity entity);

        void onRuntimeStart();
        void onRuntimeStop();

        void onUpdateRuntime(TimeStep timestep);
        void onUpdateEditor(TimeStep timestep, EditorCamera& camera);

        void onViewportResize(uint32_t width, uint32_t height);

        Entity getPrimaryCameraEntity();

    private:
        template <typename T>
        void onComponentAdded(Entity entity, T& component);

    private:
        entt::registry m_registry;
        uint32_t       m_viewport_width{0};
        uint32_t       m_viewport_height{0};

        Scope<Physics2DManager> m_physics2d_manager;
        std::list<entt::entity> m_submit_body_creation;
    };
} // namespace Toy2D