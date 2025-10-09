//
// Created by cyzho on 2025/10/8.
//

#ifndef COMPONENT_H
#define COMPONENT_H

#include "SceneCamera.h"
#include "ScriptableEntity.h"
#include "Banana/Renderer/Camera.h"
#include "glm/glm.hpp"

namespace Banana {
    struct TagComponent {
        std::string Tag;

        TagComponent() = default;

        TagComponent(const TagComponent &) = default;

        TagComponent(const std::string &tag) : Tag(tag) {
        }
    };

    struct TransformComponent {
        glm::mat4 Transform{1.0f};

        TransformComponent() = default;

        TransformComponent(const TransformComponent &) = default;

        TransformComponent(const glm::mat4 &transform) : Transform(transform) {
        }

        operator glm::mat4 &() { return Transform; }
        operator const glm::mat4 &() const { return Transform; }
    };

    struct SpriteRendererComponent {
        glm::vec4 Color{1.0f, 1.0f, 1.0f, 1.0f};

        SpriteRendererComponent() = default;

        SpriteRendererComponent(const SpriteRendererComponent &) = default;

        SpriteRendererComponent(const glm::vec4 &color): Color(color) {
        }
    };

    struct CameraComponent {
        SceneCamera Camera;
        bool Primary = true;
        bool FixedAspectRatio = false;

        CameraComponent() = default;

        CameraComponent(const CameraComponent &) = default;
    };

    struct NativeScriptComponent {
        ScriptableEntity *Instance = nullptr;

        std::function<void()> InstantiateFunction;
        std::function<void()> DestroyInstanceFunction;

        std::function<void(ScriptableEntity *)> OnCreateFunction;
        std::function<void(ScriptableEntity *)> OnDestroyFunction;
        std::function<void(ScriptableEntity *, Timestep)> OnUpdateFunction;

        template<typename T>
        void Bind() {
            InstantiateFunction = [&]() { Instance = new T(); };
            DestroyInstanceFunction = [&]() {
                delete (T *) Instance;
                Instance = nullptr;
            };

            OnCreateFunction = [](ScriptableEntity *instance) { ((T *) instance)->OnCreate(); };
            OnDestroyFunction = [](ScriptableEntity *instance) { ((T *) instance)->OnDestroy(); };
            OnUpdateFunction = [](ScriptableEntity *instance, Timestep ts) { ((T *) instance)->OnUpdate(ts); };
        }
    };
}

#endif //COMPONENT_H
