//
// Created by ChiroYuki on 09/08/2025.
//

#ifndef PIXLENGINE_TRANSFORMCOMPONENT_H
#define PIXLENGINE_TRANSFORMCOMPONENT_H

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Pixl {

    struct TransformComponent {
        glm::vec3 position{0.f};
        glm::quat rotation{1.f, 0.f, 0.f, 0.f};
        glm::vec3 scale{1.f};

        glm::mat4 worldMatrix{1.f};
        bool isDirty = true;
    };

}

#endif //PIXLENGINE_TRANSFORMCOMPONENT_H
