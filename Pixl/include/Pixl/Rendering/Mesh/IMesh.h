//
// Created by ChiroYuki on 03/08/2025.
//

#ifndef PIXLENGINE_IMESH_H
#define PIXLENGINE_IMESH_H

#include "Pixl/Rendering/RenderCommand.h"

namespace Pixl {

    class IMesh {
    public:
        virtual ~IMesh() = default;

        virtual void render(const glm::mat4& transform, const glm::mat4& viewProjection) const = 0;

        // === PROPERTIES ===
        virtual void setDrawMode(DrawMode mode) = 0;
        virtual DrawMode getDrawMode() const = 0;

        // === BOUNDING INFO ===
        virtual bool hasBounds() const { return false; }
        virtual glm::vec3 getBoundsMin() const { return glm::vec3(0.0f); }
        virtual glm::vec3 getBoundsMax() const { return glm::vec3(0.0f); }

        // === TYPE INFO ===
        virtual const char* getTypeName() const = 0;
        virtual bool isStatic() const { return true; }
        virtual bool isInstanced() const { return false; }
        virtual bool isAnimated() const { return false; }
    };

}

#endif //PIXLENGINE_IMESH_H
