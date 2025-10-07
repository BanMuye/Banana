//
// Created by 周春阳 on 2025/9/11.
//

#ifndef BANANA_ORTHOGRAPHICCAMERACONTROLLER_H
#define BANANA_ORTHOGRAPHICCAMERACONTROLLER_H
#include "Timestep.h"
#include "Banana/Events/ApplicationEvent.h"
#include "Banana/Events/Event.h"
#include "Banana/Events/MouseEvent.h"
#include "Banana/Renderer/OrthographicCamera.h"

namespace Banana {
    class OrthographicCameraController {
    public:
        OrthographicCameraController(float aspectRatio, bool rotation = false);

        void OnUpdate(Timestep ts);

        void OnEvent(Event &event);

        void OnResize(float width, float height);

        OrthographicCamera &GetCamera() { return m_Camera; }
        const OrthographicCamera &GetCamera() const { return m_Camera; }

        float GetZoomLevel() const { return m_ZoomLevel; }
        void SetZoomLevel(float level) { m_ZoomLevel = level; }

    private:
        bool OnMouseScrolled(MouseScrolledEvent &event);

        bool OnWindowResized(WindowResizeEvent &event);

    private:
        float m_AspectRatio;
        float m_ZoomLevel = 1.0f;
        OrthographicCamera m_Camera;

        bool m_Rotation;
        glm::vec3 m_CameraPosition = {0.0f, 0.0f, 0.0f};
        float m_CameraRotation = 0.0f;
        float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;
    };
}


#endif //BANANA_ORTHOGRAPHICCAMERACONTROLLER_H
