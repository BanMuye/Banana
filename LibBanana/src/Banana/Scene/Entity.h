//
// Created by cyzho on 2025/10/8.
//

#ifndef ENTITY_H
#define ENTITY_H
#include "Banana/Core/Assert.h"
#include "Banana/Scene/Scene.h"


namespace Banana {
    class Entity {
    public:
        Entity() = default;

        Entity(const Entity &other) = default;

        Entity(entt::entity handle, Scene *scene);

        template<typename T, typename... Args>
        T &AddComponent(Args &&... args) {
            BANANA_CORE_ASSERT(!HasComponent<T>(), "Entity already exists");
            return m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
        }

        template<typename T>
        T &GetComponent() {
            BANANA_CORE_ASSERT(HasComponent<T>(), "Entity dose not have such component!");
            return m_Scene->m_Registry.get<T>(m_EntityHandle);
        }

        template<typename T>
        bool HasComponent() {
            return m_Scene->m_Registry.all_of<T>(m_EntityHandle);
        }

        template<typename T>
        void RemoveComponent() {
            BANANA_CORE_ASSERT(HasComponent<T>(), "Entity does not have such component!");
            m_Scene->m_Registry.remove<T>(m_EntityHandle);
        }

        operator bool() const { return m_EntityHandle != entt::null; }

    private:
        entt::entity m_EntityHandle{0};
        Scene *m_Scene = nullptr;
    };
}


#endif //ENTITY_H
