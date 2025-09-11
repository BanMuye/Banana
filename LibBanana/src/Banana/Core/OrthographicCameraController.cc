//
// Created by 周春阳 on 2025/9/11.
//

#include "Banana/Core/bapch.h"
#include "OrthographicCameraController.h"

#include "Input.h"
#include "KeyCodes.h"

namespace Banana {
    OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation) : m_AspectRatio(
            aspectRatio), m_Rotation(rotation),
        m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel) {
    }

    void OrthographicCameraController::OnUpdate(Timestep ts) {
        if (Input::IsKeyPressed(BANANA_KEY_A)) m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
        else if (Input::IsKeyPressed(BANANA_KEY_D)) m_CameraPosition.x += m_CameraTranslationSpeed * ts;
        else if (Input::IsKeyPressed(BANANA_KEY_W)) m_CameraPosition.y += m_CameraTranslationSpeed * ts;
        else if (Input::IsKeyPressed(BANANA_KEY_S)) m_CameraPosition.y -= m_CameraTranslationSpeed * ts;

        if (m_Rotation) {
            if (Input::IsKeyPressed(BANANA_KEY_Q)) m_CameraRotation -= m_CameraRotationSpeed * ts;
            else if (Input::IsKeyPressed(BANANA_KEY_E)) m_CameraRotation += m_CameraRotationSpeed * ts;
            m_Camera.SetRotation(m_CameraRotation);
        }

        m_Camera.SetPosition(m_CameraPosition);
        m_CameraTranslationSpeed = m_ZoomLevel;
    }

    void OrthographicCameraController::OnEvent(Event &event) {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<MouseScrolledEvent>(BANANA_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
        dispatcher.Dispatch<WindowResizeEvent>(BANANA_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
    }

    bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent &event) {
        m_ZoomLevel -= event.GetYOffset() * 0.25f;
        m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
        m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        return false;
    }

    bool OrthographicCameraController::OnWindowResized(WindowResizeEvent &event) {
        m_AspectRatio = (float) event.GetWidth() / (float) event.GetHeight();
        m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        return false;
    }
}
