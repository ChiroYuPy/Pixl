//
// Created by ChiroYuki on 02/08/2025.
//

#ifndef PIXLENGINE_COLORMATERIAL_H
#define PIXLENGINE_COLORMATERIAL_H

#include "Pixl/Rendering/Objects/Shader.h"
#include "Material.h"

namespace Pixl {

    class ColorMaterial : public Material {
    private:
        Shader shader;
        glm::vec4 color;

    public:
        explicit ColorMaterial(const glm::vec4& col);

        void bind() const override;

        void unbind() const override;

        void setColor(const glm::vec4& col);
    };

}

#endif //PIXLENGINE_COLORMATERIAL_H
