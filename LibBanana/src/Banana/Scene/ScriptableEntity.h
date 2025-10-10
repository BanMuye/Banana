//
// Created by cyzho on 2025/10/8.
//

#ifndef SCRIPTABLEENTITY_H
#define SCRIPTABLEENTITY_H
#include "Entity.h"

namespace Banana {
    class ScriptableEntity {
    public:
        virtual ~ScriptableEntity(){};

        template<typename T>
        T &GetComponent() {
            return m_Entity.GetComponent<T>();
        }

    protected:
        virtual void OnCreate() {}
        virtual void OnDestroy() {}
        virtual void OnUpdate(Timestep) {}

    private:
        Entity m_Entity;
        friend class Scene;
    };
}

#endif //SCRIPTABLEENTITY_H
