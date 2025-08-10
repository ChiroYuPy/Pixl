//
// Created by ChiroYuki on 09/08/2025.
//

#ifndef PIXLENGINE_RENDERSYSTEM_H
#define PIXLENGINE_RENDERSYSTEM_H

#include "Pixl/Core/ECS/ISystem.h"
#include "Pixl/Components/Transform.h"

namespace Pixl {

    class RenderSystem : public ISystem {
    public:
        void update(Scene& scene, Time deltaTime) override {
            auto& registry = scene.getRegistry();
            auto view = registry.view<Transform>();
            for (auto entity : view) {
                auto& transform = view.get<Transform>(entity);
                printf("Rendering entity at position %.2f, %.2f, %.2f\n",
                       transform.position.x,
                       transform.position.y,
                       transform.position.z);
            }
        }
    };

}

#endif //PIXLENGINE_RENDERSYSTEM_H
