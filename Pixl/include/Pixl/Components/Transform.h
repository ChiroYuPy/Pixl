//
// Created by ChiroYuki on 09/08/2025.
//

#ifndef PIXLENGINE_TRANSFORM_H
#define PIXLENGINE_TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Pixl {

    struct Transform {
        glm::vec3 position{0.f, 0.f, 0.f};
        glm::quat rotation{1.f, 0.f, 0.f, 0.f};
        glm::vec3 scale{1.f, 1.f, 1.f};
        glm::mat4 localMatrix{1.f};
        glm::mat4 worldMatrix{1.f};
        bool isDirty = true;
    };

}

#endif //PIXLENGINE_TRANSFORM_H
