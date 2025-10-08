//
// Created by cyzho on 2025/10/8.
//

#include "Scene.h"

#include "Component.h"
#include "Banana/Renderer/Renderer2D.h"
#include "glm/glm.hpp"
#include "Banana/Scene/Entity.h"

namespace Banana {
    static void DoMatch(const glm::mat4 &transform) {
    }

    static void OnTransformConstruct(entt::registry &registry, entt::entity entity) {
    }

    Scene::Scene() {
    }

    Scene::~Scene() {
    }

    Entity Scene::CreateEntity(const std::string &name) {
        Entity entity = {m_Registry.create(), this};

        entity.AddComponent<TransformComponent>();
        auto & tag = entity.AddComponent<TagComponent>();
        tag.Tag = name.empty()? "Entity":name;
        return entity;
    }

    void Scene::OnUpdate(Timestep ts) {

        {
            m_Registry.view<NativeScriptComponent>().each([=](entt::entity entity, NativeScriptComponent& nsc) {

                if (!nsc.Instance) {
                    nsc.InstantiateFunction();
                    nsc.Instance->m_Entity = Entity {entity, this};

                    if (nsc.OnCreateFunction) {
                        nsc.OnCreateFunction(nsc.Instance);
                    }
                }

                if (nsc.OnUpdateFunction) {
                    nsc.OnUpdateFunction(nsc.Instance, ts);
                }
            });
        }

        Camera *mainCamera = nullptr;
        glm::mat4* cameraTransform = nullptr;
        {
            auto group = m_Registry.view<TransformComponent, CameraComponent>();
            for (auto entity: group) {
                const auto& [transform, camera]  = group.get<TransformComponent, CameraComponent>(entity);

                if (camera.Primary) {
                    mainCamera = &camera.Camera;
                    cameraTransform = &transform.Transform;
                    break;
                }
            }
        }

        if (mainCamera) {
           Renderer2D::BeginScene(mainCamera->GetProject(), *cameraTransform);
        }

        auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
        for (auto entity: group) {
            const auto &[transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

            Renderer2D::DrawQuad(transform, sprite.Color);
        }

        Renderer2D::EndScene();
    }
}
