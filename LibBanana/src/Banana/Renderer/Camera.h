//
// Created by cyzho on 2025/10/8.
//

#ifndef CAMERA_H
#define CAMERA_H

#include "glm/glm.hpp"

namespace Banana {
    class Camera {
    public:
        Camera() = default;

        Camera(const glm::mat4 &projection): m_Projection(projection) {
        }

        virtual ~Camera() = default;

        const glm::mat4 &GetProjection() const { return m_Projection; }

    protected:
        glm::mat4 m_Projection{1.0f};
    };
}

#endif //CAMERA_H
