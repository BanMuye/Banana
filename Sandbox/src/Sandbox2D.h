//
// Created by 周春阳 on 2025/9/11.
//

#ifndef BANANA_SANDBOX2D_H
#define BANANA_SANDBOX2D_H
#include "Banana/Core/Layer.h"
#include "Banana/Core/OrthographicCameraController.h"
#include "Banana/Renderer/Shader.h"
#include "Banana/Renderer/Texture.h"
#include "Banana/Renderer/VertexArray.h"


class Sandbox2D : public Banana::Layer {
public:
    Sandbox2D();

    virtual ~Sandbox2D() = default;

    virtual void OnAttach() override;

    virtual void OnDetach() override;

    void OnUpdate(Banana::Timestep ts) override;

    virtual void OnImGuiRender() override;

    void OnEvent(Banana::Event &event) override;

private:
    Banana::OrthographicCameraController m_CameraController;

    // Temp
    Banana::Ref<Banana::VertexArray> m_SquareVA;
    Banana::Ref<Banana::Shader> m_FlatColorShader;

    Banana::Ref<Banana::Texture2D> m_Texture;

    glm::vec4 m_SquareColor{0.2f, 0.2f, 0.5f, 1.0f};
};


#endif //BANANA_SANDBOX2D_H
