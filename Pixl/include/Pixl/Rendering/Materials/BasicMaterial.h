//
// Created by ChiroYuki on 02/08/2025.
//

#ifndef PIXLENGINE_BASICMATERIAL_H
#define PIXLENGINE_BASICMATERIAL_H

#include "Pixl/Rendering/Objects/Shader.h"
#include "IMaterial.h"

namespace Pixl {

    class BasicMaterial : public IMaterial {
    private:
        Shader shader;
        glm::vec4 color;

    public:
        BasicMaterial(const glm::vec4 &color);

        void bind() const override;
    };

}

#endif //PIXLENGINE_BASICMATERIAL_H
