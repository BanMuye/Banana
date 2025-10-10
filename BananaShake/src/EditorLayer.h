//
// Created by cyzho on 2025/10/7.
//

#ifndef EDITORLAYER_H
#define EDITORLAYER_H
#include "Banana/Core/Layer.h"
#include "Banana/Core/OrthographicCameraController.h"
#include "Banana/Renderer/Framebuffer.h"
#include "Banana/Renderer/Shader.h"
#include "Banana/Renderer/Texture.h"
#include "Banana/Renderer/VertexArray.h"
#include "Banana/Scene/Entity.h"
#include "Banana/Scene/Scene.h"
#include "Panels/SceneHierarchyPanel.h"


namespace Banana {
    class EditorLayer : public Layer {
    public:
        EditorLayer();

        ~EditorLayer() override = default;

        void OnAttach() override;

        void OnDetach() override;

        void OnUpdate(Timestep ts) override;

        void OnImGuiRender() override;

        void OnEvent(Event &event) override;

    private:
        Banana::OrthographicCameraController m_CameraController;

        // Temp
        Ref<VertexArray> m_SquareVA;
        Ref<Shader> m_FlatColorShader;

        Ref<Framebuffer> m_Framebuffer;

        Ref<Scene> m_ActiveScene;
        Entity m_SquareEntity;

        Entity m_CameraEntity;
        Entity m_SecondCamera;

        bool m_PrimaryCamera = true;

        Ref<Texture2D> m_CheckerboardTexture;

        bool m_ViewportFocused = false, m_ViewportHovered = false;

        glm::vec2 m_ViewportSize = {0.0f, 0.0f};
        glm::vec4 m_SquareColor = {0.2f, 0.3f, 0.8f, 1.0f};

        SceneHierarchyPanel m_SceneHierarchyPanel;
    };
}


#endif //EDITORLAYER_H
