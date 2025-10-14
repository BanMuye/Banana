//
// Created by cyzho on 2025/10/13.
//

#ifndef MATH_H
#define MATH_H
#include "glm/fwd.hpp"


namespace Banana::Math {

        bool DecomposeTransform(const glm::mat4 &transform, glm::vec3 &outTranslation, glm::vec3 &outRotation,
                                glm::vec3 &outScale);
}


#endif //MATH_H
