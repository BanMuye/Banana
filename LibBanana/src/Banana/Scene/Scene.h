//
// Created by cyzho on 2025/10/8.
//

#ifndef SCENE_H
#define SCENE_H

#include <cstdint>

#include "Banana/Core/Timestep.h"
#include "Banana/Renderer/EditorCamera.h"
#include "box2d/b2_world.h"
#include "entt/entt.hpp"

namespace Banana {
    class Entity;

    class Scene {
    public:
        Scene();
        ~Scene();

        Entity CreateEntity(const std::string &name = std::string());

        void DestroyEntity(Entity entity);

        void OnRuntimeStart();

        void OnRuntimeStop();

        // TEMP
        entt::registry &Reg() { return m_Registry; }

        void OnUpdateRuntime(Timestep ts);

        void OnUpdateEditor(Timestep ts, EditorCamera &camera);

        void OnViewportResize(uint32_t width, uint32_t height);

        Entity GetPrimaryCameraEntity();

    private:
        template<typename T>
        void OnComponentAdded(Entity entity, T &component);

    private:
        entt::registry m_Registry;

        uint32_t m_ViewportWidth, m_ViewportHeight;

        b2World *m_PhysicsWorld = nullptr;

        friend class Entity;
        friend class SceneHierarchyPanel;
        friend class SceneSerializer;
    };
}


#endif //SCENE_H
