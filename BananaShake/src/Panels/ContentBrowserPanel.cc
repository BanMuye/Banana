//
// Created by cyzho on 2025/10/21.
//

#include "Banana/Core/bapch.h"
#include "ContentBrowserPanel.h"

#include "imgui.h"

namespace Banana {
    static const std::filesystem::path s_AssetPath = R"(D:\Files\S_Documents\Projects\Banana\BananaShake\assets)";

    ContentBrowserPanel::ContentBrowserPanel() : m_CurrentDirectory(s_AssetPath) {
        m_DirectoryIcon = Texture2D::Create(
            R"(D:\Files\S_Documents\Projects\Banana\BananaShake\Resources\Icons\ContentBrowser\DirectoryIcon.png)");
        m_FileIcon = Texture2D::Create(
            R"(D:\Files\S_Documents\Projects\Banana\BananaShake\Resources\Icons\ContentBrowser\FileIcon.png)");
    }

    void ContentBrowserPanel::OnImGuiRender() {
        ImGui::Begin("Content Browser");

        if (m_CurrentDirectory != std::filesystem::path(s_AssetPath)) {
            if (ImGui::Button("<-")) {
                m_CurrentDirectory = m_CurrentDirectory.parent_path();
            }
        }

        static float padding = 16.0f;
        static float thumbnailSize = 128.0f;
        float cellSize = thumbnailSize + padding;

        float panelWidth = ImGui::GetContentRegionAvail().x;
        int columnCount = (int) (panelWidth / cellSize);
        if (columnCount < 1) {
            columnCount = 1;
        }

        ImGui::Columns(columnCount, 0, false);


        for (auto &directoryEntry: std::filesystem::directory_iterator(m_CurrentDirectory)) {
            const auto &path = directoryEntry.path();
            auto relativePath = std::filesystem::relative(path, s_AssetPath);
            std::string fileNameString = relativePath.filename().string();

            Ref<Texture2D> icon = directoryEntry.is_directory() ? m_DirectoryIcon : m_FileIcon;
            ImGui::ImageButton(fileNameString.c_str(), icon->GetRendererID(),
                               {thumbnailSize, thumbnailSize}, {0, 1}, {1, 0});
            if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)) {
                if (directoryEntry.is_directory()) {
                    m_CurrentDirectory /= path.filename();
                }
            }

            ImGui::TextWrapped(fileNameString.c_str());
            ImGui::NextColumn();
        }

        ImGui::Columns(1);

        ImGui::SliderFloat("Thumbnail Size", &thumbnailSize, 16, 512);
        ImGui::SliderFloat("Padding", &padding, 0, 32);

        ImGui::End();
    }
}
