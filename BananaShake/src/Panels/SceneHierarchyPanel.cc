//
// Created by cyzho on 2025/10/10.
//

#include "Banana/Core/bapch.h"
#include "SceneHierarchyPanel.h"

#include "imgui.h"
#include "Banana/Scene/Component.h"

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
}
