//
// Created by ChiroYuki on 04/08/2025.
//

#ifndef PIXLENGINE_VERTEXCOLORMATERIAL_H
#define PIXLENGINE_VERTEXCOLORMATERIAL_H

#include "IMaterial.h"

namespace Pixl {

    class VertexColorMaterial : public IMaterial {
    private:
        Shader shader;

    public:
        explicit VertexColorMaterial();

        void bind() const override;

        void unbind() const override;

        const Shader& getShader() const override;

        Pixl::VertexLayout getRequiredVertexLayout() const final;
    };

}

#endif //PIXLENGINE_VERTEXCOLORMATERIAL_H
