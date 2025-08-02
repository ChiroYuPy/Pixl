//
// Created by ChiroYuki on 02/08/2025.
//

#include "Pixl/Rendering/Material/ColorMaterial.h"

namespace Pixl {

    Pixl::ColorMaterial::ColorMaterial(const glm::vec4 &col)
            : shader("color.vertex.glsl", "color.fragment.glsl"), color(col) {}

    void Pixl::ColorMaterial::bind() const {
        shader.bind();
        // shader.setFloat4("u_Color", color);
    }

    void Pixl::ColorMaterial::unbind() const {
        shader.unbind();
    }

    void Pixl::ColorMaterial::setColor(const glm::vec4 &col) {
        color = col;
    }

}