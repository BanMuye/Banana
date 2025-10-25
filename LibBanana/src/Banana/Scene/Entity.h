//
// Created by cyzho on 2025/10/8.
//

#ifndef ENTITY_H
#define ENTITY_H
#include "Banana/Core/Assert.h"
#include "Banana/Core/UUID.h"
#include "Banana/Scene/Scene.h"
#include "Component.h"


namespace Banana {

    class Entity {
    public:
        Entity() = default;

        Entity(const Entity &other) = default;

        Entity(entt::entity handle, Scene *scene);

        template<typename T, typename... Args>
        T &AddComponent(Args &&... args) {
            BANANA_CORE_ASSERT(!HasComponent<T>(), "Entity already exists");
            T &compoennt = m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
            m_Scene->OnComponentAdded<T>(*this, compoennt);
            return compoennt;
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

        UUID GetUUID() { return GetComponent<IDComponent>().ID; }

        operator bool() const { return m_EntityHandle != entt::null; }
        operator uint32_t() const { return (uint32_t) m_EntityHandle; }
        operator entt::entity() const { return m_EntityHandle; }

        bool operator==(const Entity &other) const {
            return m_EntityHandle == other.m_EntityHandle && m_Scene == other.m_Scene;
        }

        bool operator !=(const Entity &other) const { return !(*this == other); }

    private:
        entt::entity m_EntityHandle = entt::null;
        Scene *m_Scene = nullptr;
    };
}


#endif //ENTITY_H
