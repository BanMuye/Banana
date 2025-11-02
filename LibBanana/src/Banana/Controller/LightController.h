// Created by cyzho on 2025/10/31.
//
//

#ifndef LIGHTCONTROLLER_H
#define LIGHTCONTROLLER_H
#include <entt/entity/registry.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "Banana/Core/Core.h"

namespace Banana {
    struct alignas(16) DirectionalLight {
        glm::vec4 Direction;
        glm::vec4 Color;
    };

    struct alignas(16) PointLight {
        glm::vec4 Position;
        float Constant;
        float Linear;
        float Quadratic;
        float _pad;
        glm::vec4 Color;
    };

    struct alignas(16) SpotLight {
        glm::vec4 Position;
        glm::vec4 Direction;
        float CutOff;
        float _pad[3];
        glm::vec4 Color;
    };

    static constexpr uint32_t MaxDirectionalLightCount = 1;
    static constexpr uint32_t MaxPointLightCount = 100;
    static constexpr uint32_t MaxSpotLightCount = 100;

    struct alignas(16) LightData {
        uint32_t directionalLightCount;
        uint32_t pointLightCount;
        uint32_t spotLightCount;
        float _pad;

        DirectionalLight DirectionalLights[MaxDirectionalLightCount];
        PointLight PointLights[MaxPointLightCount];
        SpotLight SpotLights[MaxSpotLightCount];
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
