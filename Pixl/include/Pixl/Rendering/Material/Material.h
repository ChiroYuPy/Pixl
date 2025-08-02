//
// Created by ChiroYuki on 02/08/2025.
//

#ifndef PIXLENGINE_MATERIAL_H
#define PIXLENGINE_MATERIAL_H

#include "Pixl/Rendering/Objects/Shader.h"

namespace Pixl {

    class Material {
    public:
        virtual void bind() const = 0;
        virtual void unbind() const = 0;
        virtual const Shader& getShader() const = 0;
        virtual ~Material() = default;
    };

}

#endif //PIXLENGINE_MATERIAL_H
