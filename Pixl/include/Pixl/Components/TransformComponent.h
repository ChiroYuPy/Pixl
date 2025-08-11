//
// Created by ChiroYuki on 09/08/2025.
//

#ifndef PIXLENGINE_TRANSFORMCOMPONENT_H
#define PIXLENGINE_TRANSFORMCOMPONENT_H

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Pixl {

    struct TransformComponent {
        glm::vec3 position{0.f, 0.f, 0.f};
        glm::quat rotation{1.f, 0.f, 0.f, 0.f};
        glm::vec3 scale{1.f, 1.f, 1.f};
        glm::mat4 localMatrix{1.f};
        glm::mat4 worldMatrix{1.f};
        bool isDirty = true;

        const glm::mat4& getTransform() {
            if (isDirty) {
                localMatrix = glm::translate(glm::mat4(1.f), position)
                              * glm::mat4(rotation)
                              * glm::scale(glm::mat4(1.f), scale);
                isDirty = false;
            }
            return localMatrix;
        }
    };

}

#endif //PIXLENGINE_TRANSFORMCOMPONENT_H
