//
// Created by cyzho on 2025/10/8.
//

#include "Banana/Core/bapch.h"
#include "Entity.h"

namespace Banana {
    Entity::Entity(entt::entity handle, Scene *scene) : m_EntityHandle(handle), m_Scene(scene) {
    }
}
