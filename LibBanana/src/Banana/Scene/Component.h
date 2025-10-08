//
// Created by cyzho on 2025/10/8.
//

#ifndef COMPONENT_H
#define COMPONENT_H

#include "glm/glm.hpp"

namespace Banana {
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
}

#endif //COMPONENT_H
