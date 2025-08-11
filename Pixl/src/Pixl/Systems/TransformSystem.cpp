//
// Created by ChiroYuki on 11/08/2025.
//

#include "Pixl/Systems/TransformSystem.h"

namespace Pixl {

    void TransformSystem::update(Scene &scene, Time deltaTime) {
        auto& registry = scene.getRegistry();
        auto view = registry.view<TransformComponent>();

        for (auto entity : view) {
            auto& transform = view.get<TransformComponent>(entity);

            if (transform.isDirty) {
                updateMatrices(transform);
                transform.isDirty = false;
            }
        }
    }

    void TransformSystem::updateMatrices(TransformComponent &transform) {
        glm::mat4 translation = glm::translate(glm::mat4(1.0f), transform.position);
        glm::mat4 rotation = glm::mat4_cast(transform.rotation);
        glm::mat4 scale = glm::scale(glm::mat4(1.0f), transform.scale);

        transform.worldMatrix = translation * rotation * scale;
    }

}