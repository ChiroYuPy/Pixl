//
// Created by ChiroYuki on 02/08/2025.
//

#ifndef PIXLENGINE_IMATERIAL_H
#define PIXLENGINE_IMATERIAL_H

#include "Pixl/Rendering/Objects/Shader.h"
#include "Pixl/Rendering/Objects/VertexDeclaration.h"

namespace Pixl {

    class IMaterial {
    public:
        virtual void bind() const = 0;
        virtual void unbind() const = 0;
        virtual const Shader& getShader() const = 0;
        virtual VertexLayout getRequiredVertexLayout() const = 0;
        virtual ~IMaterial() = default;
    };

}

#endif //PIXLENGINE_IMATERIAL_H
