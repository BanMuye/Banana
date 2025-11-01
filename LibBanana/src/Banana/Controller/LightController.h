//
// Created by cyzho on 2025/10/31.
//

#ifndef LIGHTCONTROLLER_H
#define LIGHTCONTROLLER_H
#include <entt/entity/registry.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "Banana/Core/Core.h"

namespace Banana {
    struct DirectionalLight {
        glm::vec3 Direction;
        glm::vec3 Color;
    };

    struct PointLight {
        glm::vec3 Position;
        float Constant;
        float Linear;
        float Quadratic;
        glm::vec3 Color;
    };

    struct SpotLight {
        glm::vec3 Position;
        glm::vec3 Direction;
        float CutOff;
        glm::vec3 Color;
    };

    struct LightData {
        static constexpr uint32_t DirectionalLightCount = 1;
        static constexpr uint32_t PointLightCount = 100;
        static constexpr uint32_t SpotLightCount = 100;

        DirectionalLight DirectionalLights[DirectionalLightCount];
        PointLight PointLights[PointLightCount];
        SpotLight SpotLights[SpotLightCount];
    };

    class LightController {
    public:
        static glm::vec4 s_InitialLightPosition;

    public:
        LightController() = default;

        ~LightController() = default;

        void Update(entt::registry &registry);

        const LightData &GetLightData() const { return m_LightData; }

    private:
        void UpdateDirectionalLight(entt::registry &registry);

        void UpdatePointLight(entt::registry &registry);

        void UpdateSpotLight(entt::registry &registry);

    private:
        LightData m_LightData;
    };
}

#endif //LIGHTCONTROLLER_H
