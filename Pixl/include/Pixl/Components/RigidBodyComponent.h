//
// Created by ChiroYuki on 14/08/2025.
//

#ifndef PIXLENGINE_RIGIDBODYCOMPONENT_H
#define PIXLENGINE_RIGIDBODYCOMPONENT_H

#include <glm/vec3.hpp>

namespace Pixl {

    struct RigidBodyComponent {
        float mass = 1.0f;
        glm::vec3 velocity = {0, 0, 0};
        glm::vec3 acceleration = {0, 0, 0};
    };

}

#endif //PIXLENGINE_RIGIDBODYCOMPONENT_H
