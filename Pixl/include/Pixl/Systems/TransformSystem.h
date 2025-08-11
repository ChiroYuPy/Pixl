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
        void update(Scene& scene, Time deltaTime) override;

    private:
        void updateMatrices(TransformComponent& transform);
    };

}

#endif //PIXLENGINE_TRANSFORMSYSTEM_H
