//
// Created by ChiroYuki on 02/08/2025.
//

#include "Pixl/Rendering/Material/ColorMaterial.h"

namespace Pixl {

    const char* vertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_position;

            uniform mat4 u_viewProjection;
            uniform mat4 u_transform;

            void main() {
                gl_Position = u_viewProjection * u_transform * vec4(a_position, 1.0);
            }
        )";

    // Fragment Shader Source
    const char* fragmentSrc = R"(
            #version 330 core

            uniform vec4 u_color;
            out vec4 frag_color;

            void main() {
                frag_color = u_color;
            }

        )";

    ColorMaterial::ColorMaterial(const glm::vec4 &col)
            : shader(vertexSrc, fragmentSrc), color(col) {}

    void ColorMaterial::bind() const {
        shader.bind();
        shader.setFloat4("u_color", color);
    }

    void ColorMaterial::unbind() const {
        shader.unbind();
    }

    void ColorMaterial::setColor(const glm::vec4 &col) {
        color = col;
    }

    const Shader &ColorMaterial::getShader() const {
        return shader;
    }

}