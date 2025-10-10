//
// Created by cyzho on 2025/10/10.
//

#include "Banana/Core/bapch.h"
#include "SceneHierarchyPanel.h"

#include "imgui.h"
#include "Banana/Scene/Component.h"
#include "glm/gtc/type_ptr.hpp"

namespace Banana {
    SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene> &scene) {
        SetContext(scene);
    }

    void SceneHierarchyPanel::OnImGuiRender() {
        ImGui::Begin("Scene Hierarchy");

        const auto &view = m_Context->m_Registry.view<TagComponent>();
        for (auto entity: view) {
            Entity currentEntity{entity, m_Context.get()};
            DrawEntityNode(currentEntity);
        }

        if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered()) {
            m_SelectionContext = {};
        }

        ImGui::End();

        ImGui::Begin("Properties");
        if (m_SelectionContext) {
            DrawComponents(m_SelectionContext);
        }

        ImGui::End();
    }

    void SceneHierarchyPanel::DrawEntityNode(Entity entity) {
        auto &tag = entity.GetComponent<TagComponent>().Tag;
        ImGuiTreeNodeFlags flags = ((m_SelectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) |
                                   ImGuiTreeNodeFlags_OpenOnArrow;
        bool opened = ImGui::TreeNodeEx((void *) (uint64_t) (uint32_t) entity, flags, tag.c_str());
        if (ImGui::IsItemClicked()) {
            m_SelectionContext = entity;
        }

        if (opened) {
            ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
            bool opened = ImGui::TreeNodeEx((void *) (uint64_t) (uint32_t) 998988, flags, tag.c_str());
            if (opened) {
                ImGui::TreePop();
            }
            ImGui::TreePop();
        }
    }

    void SceneHierarchyPanel::DrawComponents(Entity entity) {
        if (entity.HasComponent<TagComponent>()) {
            auto &tag = entity.GetComponent<TagComponent>().Tag;
            char buffer[256];
            memset(buffer, 0, sizeof(buffer));
            strcpy_s(buffer, sizeof(buffer), tag.c_str());
            if (ImGui::InputText("Tag", buffer, sizeof(buffer))) {
                tag = std::string(buffer);
            }
        }

        if (entity.HasComponent<TransformComponent>()) {
            if (ImGui::TreeNodeEx((void *) typeid(TransformComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen,
                                  "Transform")) {
                auto &transform = entity.GetComponent<TransformComponent>().Transform;
                ImGui::DragFloat3("Position", glm::value_ptr(transform[3]), 0.1f);
                ImGui::TreePop();
            }
        }

        if (entity.HasComponent<CameraComponent>()) {
            if (ImGui::TreeNodeEx((void *) typeid(CameraComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen,
                                  "Camera")) {
                auto &cameraComponent = entity.GetComponent<CameraComponent>();
                auto &camera = cameraComponent.Camera;

                ImGui::Checkbox("Primary", &cameraComponent.Primary);

                const char *projectionTypeStrings[] = {"Perspective", "Orthographic"};
                const char *currentProjectionTypeString = projectionTypeStrings[(int) camera.GetProjectionType()];
                if (ImGui::BeginCombo("Projection", currentProjectionTypeString)) {
                    for (int i = 0; i < 2; i++) {
                        bool isSelected = currentProjectionTypeString == projectionTypeStrings[i];
                        if (ImGui::Selectable(projectionTypeStrings[i], isSelected)) {
                            currentProjectionTypeString = projectionTypeStrings[i];
                            camera.SetProjectionType((SceneCamera::ProjectionType) i);
                        }
                        if (isSelected) {
                            ImGui::SetItemDefaultFocus();
                        }
                    }
                    ImGui::EndCombo();
                }

                if (camera.GetProjectionType() == SceneCamera::ProjectionType::Perspective) {
                    float verticalFov = glm::degrees(camera.GetPerspectiveVerticalFOV());
                    if (ImGui::DragFloat("Vertical FOV", &verticalFov)) {
                        camera.SetPerspectiveVerticalFOV(glm::radians(verticalFov));
                    }

                    float perspectiveNear = camera.GetPerspectiveNearClip();
                    if (ImGui::DragFloat("Near", &perspectiveNear)) {
                        camera.SetPerspectiveNearClip(perspectiveNear);
                    }

                    float perspectiveFar = camera.GetPerspectiveFarClip();
                    if (ImGui::DragFloat("Far", &perspectiveFar)) {
                        camera.SetPerspectiveFarClip(perspectiveFar);
                    }
                }

                if (camera.GetProjectionType() == SceneCamera::ProjectionType::Orthographic) {
                    float orthographicSize = camera.GetOrthoGraphicSize();
                    if (ImGui::DragFloat("Size", &orthographicSize)) {
                        camera.SetOrthographicSize(orthographicSize);
                    }

                    float orthographicNear = camera.GetOrthographicNearClip();
                    if (ImGui::DragFloat("Near", &orthographicNear)) {
                        camera.SetOrthographicNearClip(orthographicNear);
                    }

                    float orthographicFar = camera.GetOrthographicFarClip();
                    if (ImGui::DragFloat("Far", &orthographicFar)) {
                        camera.SetOrthographicFarClip(orthographicFar);
                    }

                    ImGui::Checkbox("Fixed Aspect Ratio", &cameraComponent.FixedAspectRatio);
                }

                ImGui::TreePop();
            }
        }
    }
}
