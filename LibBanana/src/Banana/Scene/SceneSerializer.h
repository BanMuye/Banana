//
// Created by cyzho on 2025/10/12.
//

#ifndef SCENESERIALIZER_H
#define SCENESERIALIZER_H
#include <string>

#include "Scene.h"
#include "Banana/Core/Core.h"

namespace Banana {
    class SceneSerializer {
    public:
        SceneSerializer(const Ref<Scene> &scene);

        void Serialize(const std::string &filepath);

        void SerializeRuntime(const std::string &filepath);

        bool Deserialize(const std::string &filepath);

        bool DeserializeRuntime(const std::string &filepath);

    private:
        Ref<Scene> m_Scene;
    };
}


#endif //SCENESERIALIZER_H
