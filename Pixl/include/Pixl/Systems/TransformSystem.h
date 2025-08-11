//
// Created by ChiroYuki on 10/08/2025.
//

#ifndef PIXLENGINE_TRANSFORMSYSTEM_H
#define PIXLENGINE_TRANSFORMSYSTEM_H

#include "Pixl/Components/TransformComponent.h"
#include "Pixl/Core/Time/Time.h"
#include "Pixl/Core/ECS/Scene.h"
#include "Pixl/Core/ECS/ISystem.h"

namespace Pixl {

    class TransformSystem : public ISystem {
    public:
        void update(Scene& scene, Time deltaTime) override {
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

    private:
        void updateMatrices(TransformComponent& transform) {
            // Calculer la matrice locale
            glm::mat4 translation = glm::translate(glm::mat4(1.0f), transform.position);
            glm::mat4 rotation = glm::mat4_cast(transform.rotation);
            glm::mat4 scale = glm::scale(glm::mat4(1.0f), transform.scale);

            transform.localMatrix = translation * rotation * scale;
            transform.worldMatrix = transform.localMatrix;
        }
    };

}

#endif //PIXLENGINE_TRANSFORMSYSTEM_H
