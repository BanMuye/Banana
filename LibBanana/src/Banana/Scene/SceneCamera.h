//
// Created by cyzho on 2025/10/9.
//

#ifndef SCENECAMERA_H
#define SCENECAMERA_H

#include "Banana/Renderer/Camera.h"


namespace Banana {
    class SceneCamera : public Camera {
    public:
        SceneCamera();

        virtual ~SceneCamera() = default;

        void SetOrthographic(float size, float nearClip, float farClip);

        void SetViewportSize(uint32_t width, uint32_t height);

        float GetOrthoGraphicSize() const { return m_OrthographicSize; }
        void SetOrthographicSize(float size) { m_OrthographicSize = size; }

    private:
        void RecalculateProjection();

    private:
        float m_OrthographicSize = 10.0f;
        float m_OrthographicNear = -1.0f, m_OrthographicFar = 1.0f;
        float m_AspectRatio = 0.0f;
    };
}


#endif //SCENECAMERA_H
