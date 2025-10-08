//
// Created by cyzho on 2025/10/8.
//

#ifndef SCENE_H
#define SCENE_H

#include "Banana/Core/Timestep.h"
#include "entt/entt.hpp"

namespace Banana {
    class Scene {
    public:
        Scene();

        ~Scene();

        entt::entity CreateEntity();

        // TEMP
        entt::registry &Reg() { return m_Registry; }

        void OnUpdate(Timestep ts);

    private:
        entt::registry m_Registry;
    };
}


#endif //SCENE_H
