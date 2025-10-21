#include "EditorLayer.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui.h"
#include "ImGuizmo.h"
#include "Banana/Core/Application.h"
#include "Banana/Core/Input.h"
#include "Banana/Core/KeyCodes.h"
#include "Banana/Math/Math.h"
#include "Banana/Renderer/RenderCommand.h"
#include "Banana/Renderer/Renderer2D.h"
#include "Banana/Scene/Component.h"
#include "Banana/Scene/SceneSerializer.h"
#include "Banana/Utils/PlatformUtils.h"

namespace Banana {
    extern const std::filesystem::path g_AssetPath;

    EditorLayer::EditorLayer()
        : Layer("EditorLayer"), m_CameraController(1280.0f / 720.0f), m_SquareColor({0.2f, 0.3f, 0.8f, 1.0f}) {
    }

    void EditorLayer::OnAttach() {
        BANANA_PROFILE_FUNCTION();

        m_CheckerboardTexture = Texture2D::Create("assets\\textures\\Checkerboard.png");

        FramebufferSpecification fbSpec;
        fbSpec.Width = 1280;
        fbSpec.Height = 720;
        fbSpec.Attachments = {
            FramebufferTextureFormat::RGBA8, FramebufferTextureFormat::RED_INTEGER, FramebufferTextureFormat::Depth
        };
        m_Framebuffer = Framebuffer::Create(fbSpec);

        m_ActiveScene = std::make_shared<Scene>();

        m_EditorCamera = EditorCamera(30.0f, 1.778f, 0.1f, 1000.0f);

        m_SceneHierarchyPanel.SetContext(m_ActiveScene);

        auto commandLineArgs = Application::Get().GetCommandLineArgs();
        if (commandLineArgs.Count > 1) {
            auto sceneFilePath = commandLineArgs[1];
            SceneSerializer serializer(m_ActiveScene);
            serializer.Deserialize(sceneFilePath);
        }
    }

    void EditorLayer::OnDetach() {
        BANANA_PROFILE_FUNCTION();
    }

    void EditorLayer::OnUpdate(Timestep ts) {
        BANANA_PROFILE_FUNCTION();

        // Resize
        if (FramebufferSpecification specification = m_Framebuffer->GetSpecification();
            m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f && (
                specification.Width != m_ViewportSize.x || specification.Height != m_ViewportSize.y)) {
            m_Framebuffer->Resize(uint32_t(m_ViewportSize.x), uint32_t(m_ViewportSize.y));
            m_CameraController.OnResize(m_ViewportSize.x, m_ViewportSize.y);
            m_EditorCamera.SetViewportSize(m_ViewportSize.x, m_ViewportSize.y);
            m_ActiveScene->OnViewportResize(uint32_t(m_ViewportSize.x), uint32_t(m_ViewportSize.y));
        }

        // Update
        if (m_ViewportFocused)
            m_CameraController.OnUpdate(ts);

        m_EditorCamera.OnUpdate(ts);

        // Render
        Renderer2D::ResetStats(); {
            BANANA_PROFILE_SCOPE("Renderer Prep");
            m_Framebuffer->Bind();
            RenderCommand::SetClearColor({0.1f, 0.3f, 0.5f, 1});
            RenderCommand::Clear();
            m_Framebuffer->ClearAttachment(1, -1);
        } {
            static float rotation = 0.0f;
            rotation += ts * 50.0f;

            BANANA_PROFILE_SCOPE("Renderer Draw");

            m_ActiveScene->OnUpdateEditor(ts, m_EditorCamera);

            auto [mx, my] = ImGui::GetMousePos();
            mx -= m_ViewportBounds[0].x;
            my -= m_ViewportBounds[0].y;
            glm::vec2 viewportSize = m_ViewportBounds[1] - m_ViewportBounds[0];
            my = viewportSize.y - my;

            int mouseX = (int) mx;
            int mouseY = (int) my;

            if (mouseX >= 0 && mouseY >= 0 && mouseX < viewportSize.x && mouseY < viewportSize.y) {
                int pixelData = m_Framebuffer->ReadPixel(1, mouseX, mouseY);
                BANANA_CORE_WARN("Pixel data = {0}", pixelData);
                m_HoveredEntity = pixelData == -1 ? Entity() : Entity((entt::entity) pixelData, m_ActiveScene.get());
            }

            m_Framebuffer->Unbind();
        }
    }

    void EditorLayer::OnImGuiRender() {
        BANANA_PROFILE_FUNCTION();

        // Note: Switch this to true to enable dockspace
        static bool dockspaceOpen = true;
        static bool opt_fullscreen_persistant = true;
        bool opt_fullscreen = opt_fullscreen_persistant;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen) {
            ImGuiViewport *viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->Pos);
            ImGui::SetNextWindowSize(viewport->Size);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
                    ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
        ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // DockSpace
        ImGuiIO &io = ImGui::GetIO();
        ImGuiStyle &style = ImGui::GetStyle();
        float minWinSizeX = style.WindowMinSize.x;
        style.WindowMinSize.x = 370.0f;
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        style.WindowMinSize.x = minWinSizeX;

        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                // Disabling fullscreen would allow the window to be moved to the front of other windows,
                // which we can't undo at the moment without finer window depth/z control.
                //ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);

                if (ImGui::MenuItem("New", "Ctrl+N")) {
                    NewScene();
                }

                if (ImGui::MenuItem("Open...", "Ctrl+O")) {
                    OpenScene();
                }

                if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S")) {
                    SaveSceneAs();
                }

                if (ImGui::MenuItem("Exit")) Application::Get().Close();
                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }

        m_SceneHierarchyPanel.OnImGuiRender();
        m_ContentBrowserPanel.OnImGuiRender();

        ImGui::Begin("Stats");

        std::string name = "None";
        if (m_HoveredEntity) {
            name = m_HoveredEntity.GetComponent<TagComponent>().Tag;
        }
        ImGui::Text("Hovered Entity: %s", name.c_str());

        auto stats = Renderer2D::GetStats();
        ImGui::Text("Renderer2D Stats:");
        ImGui::Text("Draw Calls: %d", stats.DrawCalls);
        ImGui::Text("Quads: %d", stats.QuadCount);
        ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
        ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

        ImGui::End();

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0, 0});
        ImGui::Begin("Viewport");

        auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
        auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
        auto viewportOffset = ImGui::GetWindowPos();
        m_ViewportBounds[0] = {viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y};
        m_ViewportBounds[1] = {viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y};

        m_ViewportFocused = ImGui::IsWindowFocused();
        m_ViewportHovered = ImGui::IsWindowHovered();
        Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused && !m_ViewportHovered);

        ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
        m_ViewportSize = {viewportPanelSize.x, viewportPanelSize.y};

        uint64_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
        ImGui::Image(reinterpret_cast<void *>(textureID), ImVec2{m_ViewportSize.x, m_ViewportSize.y}, ImVec2{0, 1},
                     ImVec2{1, 0});

        if (ImGui::BeginDragDropTarget()) {
            if (const ImGuiPayload *payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM")) {
                const wchar_t *path = (const wchar_t *) payload->Data;
                OpenScene(std::filesystem::path(g_AssetPath) / path);
            }

            ImGui::EndDragDropTarget();
        }

        // Gizmos
        Entity selectedEntity = m_SceneHierarchyPanel.GetSelectedEntity();
        if (selectedEntity && m_GizmoType != -1) {
            ImGuizmo::SetOrthographic(false);
            ImGuizmo::SetDrawlist();

            float windowWidth = ImGui::GetWindowWidth();
            float windowHeight = ImGui::GetWindowHeight();
            ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);

            // Camera
            // auto cameraEntity = m_ActiveScene->GetPrimaryCameraEntity();
            // const auto &camera = cameraEntity.GetComponent<CameraComponent>().Camera;
            // const glm::mat4 &cameraProjection = camera.GetProjection();
            // glm::mat4 cameraView = glm::inverse(cameraEntity.GetComponent<TransformComponent>().GetTransform());

            // Editor Camera
            const glm::mat4 &cameraProjection = m_EditorCamera.GetProjection();
            glm::mat4 cameraView = m_EditorCamera.GetViewMatrix();

            // Entity transform
            auto &tc = selectedEntity.GetComponent<TransformComponent>();
            glm::mat4 transform = tc.GetTransform();

            // Snapping
            bool snap = Input::IsKeyPressed(Key::LeftControl);
            float snapValue = 0.5f;
            if (m_GizmoType == ImGuizmo::OPERATION::ROTATE) {
                snapValue = 45.0f;
            }

            float snapValues[3] = {snapValue, snapValue, snapValue};

            ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(cameraProjection),
                                 (ImGuizmo::OPERATION) m_GizmoType, ImGuizmo::LOCAL, glm::value_ptr(transform), nullptr,
                                 snap ? snapValues : nullptr);
            if (ImGuizmo::IsUsing()) {
                glm::vec3 translation, rotation, scale;
                Math::DecomposeTransform(transform, translation, rotation, scale);

                glm::vec3 deltaRotation = rotation - tc.Rotation;
                tc.Translation = translation;
                tc.Rotation += deltaRotation;
                tc.Scale = scale;
            }
        }


        ImGui::End();
        ImGui::PopStyleVar();

        ImGui::End();
    }


    void EditorLayer::OnEvent(Event &e) {
        m_CameraController.OnEvent(e);
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<KeyPressedEvent>(BANANA_BIND_EVENT_FN(EditorLayer::OnKeyPressed));
        dispatcher.Dispatch<MouseButtonPressedEvent>(BANANA_BIND_EVENT_FN(EditorLayer::OnMouseButtonPressed));
    }

    bool EditorLayer::OnKeyPressed(KeyPressedEvent &e) {
        if (e.GetRepeatCount() > 0) {
            return false;
        }

        bool control = Input::IsKeyPressed(KeyCode::LeftControl) || Input::IsKeyPressed(KeyCode::RightControl);
        bool shift = Input::IsKeyPressed(KeyCode::LeftShift) || Input::IsKeyPressed(KeyCode::RightShift);

        switch (e.GetKeyCode()) {
            case KeyCode::N: {
                if (control) {
                    NewScene();
                }
                break;
            }
            case KeyCode::O: {
                if (control) {
                    OpenScene();
                }
                break;
            }
            case KeyCode::S: {
                if (control && shift) {
                    SaveSceneAs();
                }
                break;
            }
            // Gizmos
            case KeyCode::Q:
                m_GizmoType = -1;
                break;
            case KeyCode::W:
                m_GizmoType = ImGuizmo::OPERATION::TRANSLATE;
                break;
            case KeyCode::E:
                m_GizmoType = ImGuizmo::OPERATION::ROTATE;
                break;
            case KeyCode::R:
                m_GizmoType = ImGuizmo::OPERATION::SCALE;
                break;
        }
        return false;
    }

    bool EditorLayer::OnMouseButtonPressed(MouseButtonPressedEvent &e) {
        if (e.GetMouseButton() == MouseCode::ButtonLeft) {
            if (m_ViewportHovered && !ImGuizmo::IsOver() && !Input::IsKeyPressed(KeyCode::LeftAlt)) {
                m_SceneHierarchyPanel.SetSelectedEntity(m_HoveredEntity);
            }
        }
        return false;
    }

    void EditorLayer::NewScene() {
        m_ActiveScene = std::make_shared<Scene>();
        m_ActiveScene->OnViewportResize((uint32_t) m_ViewportSize.x, (uint32_t) m_ViewportSize.y);
        m_SceneHierarchyPanel.SetContext(m_ActiveScene);
    }

    void EditorLayer::OpenScene() {
        std::string filepath = FileDialogs::OpenFile("Scene Files (*.banana)\0*.banana\0");
        if (!filepath.empty()) {
            OpenScene(filepath);
        }
    }

    void EditorLayer::OpenScene(const std::filesystem::path &path) {
        m_ActiveScene = std::make_shared<Scene>();
        m_ActiveScene->OnViewportResize((uint32_t) m_ViewportSize.x, (uint32_t) m_ViewportSize.y);
        m_SceneHierarchyPanel.SetContext(m_ActiveScene);

        SceneSerializer serializer(m_ActiveScene);
        serializer.Deserialize(path.string());
    }

    void EditorLayer::SaveSceneAs() {
        std::string filepath = FileDialogs::OpenFile("Scene Files (*.banana)\0*.banana\0");
        if (!filepath.empty()) {
            SceneSerializer serializer(m_ActiveScene);
            serializer.Serialize(filepath);
        }
    }
}
