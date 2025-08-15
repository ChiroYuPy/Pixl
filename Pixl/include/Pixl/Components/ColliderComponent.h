//
// Created by ChiroYuki on 14/08/2025.
//

#ifndef PIXLENGINE_COLLIDERCOMPONENT_H
#define PIXLENGINE_COLLIDERCOMPONENT_H

#include <glm/vec3.hpp>

namespace Pixl {

    enum class ColliderShape { Box, Sphere, Capsule };

    struct ColliderComponent {
        ColliderShape shape;
        glm::vec3 size;
        float radius = 1.f;
        float height;
    };

}

#endif //PIXLENGINE_COLLIDERCOMPONENT_H
