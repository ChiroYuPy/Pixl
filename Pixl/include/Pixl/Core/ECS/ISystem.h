//
// Created by ChiroYuki on 09/08/2025.
//

#ifndef PIXLENGINE_ISYSTEM_H
#define PIXLENGINE_ISYSTEM_H

#include "Pixl/Core/Time/Time.h"
#include "Pixl/Core/ECS/Scene.h"

#include <entt/entt.hpp>

namespace Pixl {

    class ISystem {
    public:
        virtual void update(Scene& scene, Time deltaTime) = 0;
        virtual ~ISystem() = default;
    };

}

#endif //PIXLENGINE_ISYSTEM_H
