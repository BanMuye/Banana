//
// Created by cyzho on 2025/10/31.
//

#include "Banana/Core/bapch.h"
#include "LightController.h"

#include "Banana/Core/Assert.h"
#include "Banana/Scene/Component.h"

namespace Banana {
    void LightController::Update(entt::registry &registry) {
        UpdateDirectionalLight(registry);
        UpdatePointLight(registry);
        UpdateSpotLight(registry);
    }


    void LightController::UpdateDirectionalLight(entt::registry &registry) {
        auto view = registry.view<DirectionalLight>();
        const auto it = view.begin();
        for (int i = 0; i < LightData::DirectionalLightCount; ++i) {
            if (it == view.end()) {
                return;
            }

            const auto &directionalLightComponent = registry.get<DirectionalLightComponent>(*it);

            m_LightData.DirectionalLights[i].Color = directionalLightComponent.Color;
            m_LightData.DirectionalLights[i].Direction = directionalLightComponent.Direction;

        }
    }

    void LightController::UpdatePointLight(entt::registry &registry) {
        auto view = registry.view<PointLightComponent, TransformComponent>();
        const auto it = view.begin();
        for (int i = 0; i < LightData::PointLightCount; ++i) {
            if (it == view.end()) {
                return;
            }

            const auto &[pointLightComponent, transformComponent] = registry.get<PointLightComponent,
                TransformComponent>(*it);
            // todo @Banmuye whether change vec4 to vec3 is safe?
            auto position = transformComponent.GetTransform() * s_InitialLightPosition;
            m_LightData.PointLights[i].Color = pointLightComponent.Color;
            m_LightData.PointLights[i].Constant = pointLightComponent.Constant;
            m_LightData.PointLights[i].Linear = pointLightComponent.Linear;
            m_LightData.PointLights[i].Quadratic = pointLightComponent.Quadratic;
            m_LightData.PointLights[i].Position = position;
        }
    }

    void LightController::UpdateSpotLight(entt::registry &registry) {
        auto view = registry.view<SpotLightComponent, TransformComponent>();
        const auto it = view.begin();
        for (int i = 0; i < LightData::SpotLightCount; ++i) {
            if (it == view.end()) {
                return;
            }

            const auto &[spotLight, transform] = registry.get<SpotLightComponent, TransformComponent>(*it);
            auto position = transform.GetTransform() * s_InitialLightPosition;
            m_LightData.SpotLights[i].Color = spotLight.Color;
            m_LightData.SpotLights[i].Direction = spotLight.Direction;
            m_LightData.SpotLights[i].Position = position;
            m_LightData.SpotLights[i].CutOff = spotLight.CutOff;
        }
    }
}
