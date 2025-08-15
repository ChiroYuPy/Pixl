//
// Created by ChiroYuki on 09/08/2025.
//

#ifndef PIXLENGINE_RENDERSYSTEM_H
#define PIXLENGINE_RENDERSYSTEM_H

#include "Pixl/Core/ECS/ISystem.h"
#include "Pixl/Components.h"
#include "Pixl/Rendering/Objects/Shader.h"
#include "Pixl/Rendering/Geometry/Geometry.h"

namespace Pixl {

    class RenderSystem : public ISystem {
    public:
        void update(Scene& scene, Time deltaTime) override;
    };

}

#endif //PIXLENGINE_RENDERSYSTEM_H
