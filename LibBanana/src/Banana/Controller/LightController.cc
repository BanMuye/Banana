//
// Created by cyzho on 2025/10/31.
//

#include "Banana/Core/bapch.h"
#include "LightController.h"

#include "Banana/Core/Assert.h"
#include "Banana/Scene/Component.h"

namespace Banana {
    glm::vec4 LightController::s_InitialLightPosition = {0.0f, 0.0f, 0.0f, 1.0f};

    void LightController::Update(entt::registry &registry) {
        UpdateDirectionalLight(registry);
        UpdatePointLight(registry);
        UpdateSpotLight(registry);
    }


    void LightController::UpdateDirectionalLight(entt::registry &registry) {
        auto view = registry.view<DirectionalLightComponent>();
        int i = 0;
        for (auto entity: view) {
            if (i >= MaxDirectionalLightCount) { break; }

            const auto &directionalLightComponent = registry.get<DirectionalLightComponent>(entity);

            m_LightData.DirectionalLights[i].Color = directionalLightComponent.Color;
            m_LightData.DirectionalLights[i].Direction = directionalLightComponent.Direction;
            i++;
        }

        m_LightData.directionalLightCount = i;
    }

    void LightController::UpdatePointLight(entt::registry &registry) {
        auto view = registry.view<PointLightComponent, TransformComponent>();
        int i = 0;
        for (auto entity: view) {
            if (i >= MaxPointLightCount) { break; }

            const auto &[pointLightComponent, transformComponent] = registry.get<PointLightComponent,
                TransformComponent>(entity);
            // todo @Banmuye whether change vec4 to vec3 is safe?
            auto position = transformComponent.GetTransform() * s_InitialLightPosition;
            m_LightData.PointLights[i].Color = pointLightComponent.Color;
            m_LightData.PointLights[i].Constant = pointLightComponent.Constant;
            m_LightData.PointLights[i].Linear = pointLightComponent.Linear;
            m_LightData.PointLights[i].Quadratic = pointLightComponent.Quadratic;
            m_LightData.PointLights[i].Position = position;

            i++;
        }

        m_LightData.pointLightCount = i;
    }

    void LightController::UpdateSpotLight(entt::registry &registry) {
        auto view = registry.view<SpotLightComponent, TransformComponent>();
        int i = 0;
        for (auto entity: view) {
            if (i >= MaxSpotLightCount) { break; }

            const auto &[spotLight, transform] = registry.get<SpotLightComponent, TransformComponent>(entity);
            auto position = transform.GetTransform() * s_InitialLightPosition;
            m_LightData.SpotLights[i].Color = spotLight.Color;
            m_LightData.SpotLights[i].Direction = spotLight.Direction;
            m_LightData.SpotLights[i].Position = position;
            m_LightData.SpotLights[i].CutOff = spotLight.CutOff;
            m_LightData.SpotLights[i].OuterCutOff = spotLight.OutterCutOff;

            i++;
        }

        m_LightData.spotLightCount = i;
    }
}
