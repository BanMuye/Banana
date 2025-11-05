//
// Created by cyzho on 2025/10/8.
//

#ifndef SCENE_H
#define SCENE_H

#include <cstdint>

#include "Banana/Controller/LightController.h"
#include "Banana/Core/Timestep.h"
#include "Banana/Core/UUID.h"
#include "Banana/Renderer/EditorCamera.h"
#include "Banana/Renderer/Framebuffer.h"
#include "box2d/b2_world.h"
#include "entt/entt.hpp"

namespace Banana {
    class Entity;

    class Scene {
    public:
        Scene();

        ~Scene();

        static Ref<Scene> Copy(Ref<Scene> other);

        Entity CreateEntity(const std::string &name = std::string());

        Entity CreateEntityWithUUID(UUID uuid, const std::string &name = std::string());

        void DestroyEntity(Entity entity);

        void OnRuntimeStart();

        void OnRuntimeStop();

        // TEMP
        entt::registry &Reg() { return m_Registry; }

        void OnUpdateRuntime(Timestep ts);

        void OnUpdateEditor(Timestep ts, EditorCamera &camera);

        void OnViewportResize(uint32_t width, uint32_t height);

        void DuplicateEntity(Entity entity);

        uint32_t GetViewportWidth() const { return m_ViewportWidth; }
        uint32_t GetViewportHeight() const { return m_ViewportHeight; }
        Ref<Framebuffer> GetRenderFramebuffer() { return m_ShadowFrameBuffer; }

        Entity GetPrimaryCameraEntity();

        template<typename... Component>
        auto GetAllEntitiesWith() {
            return m_Registry.view<Component...>();
        }

    private:
        template<typename T>
        void OnComponentAdded(Entity entity, T &component);

        void Clear();

        void Render2DOnEdit(EditorCamera &camera, Timestep ts);

        void RenderShadowOnEdit();

        void Render3DOnEdit(EditorCamera &camera, Timestep ts);

    private:
        entt::registry m_Registry;

        uint32_t m_ViewportWidth, m_ViewportHeight;

        b2World *m_PhysicsWorld = nullptr;

        LightController m_LightController;

        Ref<Framebuffer> m_ShadowFrameBuffer;
        Ref<Framebuffer> m_ViewFrameBuffer;

        friend class Entity;
        friend class SceneHierarchyPanel;
        friend class SceneSerializer;
    };
}


#endif //SCENE_H
