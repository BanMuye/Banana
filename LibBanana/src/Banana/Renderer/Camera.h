//
// Created by cyzho on 2025/10/8.
//

#ifndef CAMERA_H
#define CAMERA_H

#include "glm/glm.hpp"

namespace Banana {
    class Camera {
    public:
        Camera(const glm::mat4 &projection): m_Projection(projection) {
        }

        const glm::mat4 &GetProject() const { return m_Projection; }

    private:
        glm::mat4 m_Projection;
    };
}

#endif //CAMERA_H
