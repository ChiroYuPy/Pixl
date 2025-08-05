//
// Created by ChiroYuki on 02/08/2025.
//

#ifndef PIXLENGINE_UNLITMATERIAL_H
#define PIXLENGINE_UNLITMATERIAL_H

#include "Pixl/Rendering/Objects/Shader.h"
#include "Material.h"

namespace Pixl {

    class UnlitMaterial : public Material {
    public:
        explicit UnlitMaterial(Ref<Shader> shader);

        void setColor(const glm::vec4& col);

        void bind() const override;

    private:
        glm::vec4 m_color = glm::vec4(1.0f);
    };

}

#endif //PIXLENGINE_UNLITMATERIAL_H
