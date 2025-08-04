//
// Created by ChiroYuki on 04/08/2025.
//

#include "Pixl/Rendering/Material/VertexColorMaterial.h"

namespace Pixl {

    const char* vertexSrcVertexColorMaterial = R"(
            #version 330 core

            layout(location = 0) in vec3 a_position;
            layout(location = 1) in vec4 a_color;

            uniform mat4 u_viewProjection;
            uniform mat4 u_transform;

            out vec4 i_color;

            void main()
            {
                i_color = a_color;
                gl_Position = u_viewProjection * u_transform * vec4(a_position, 1.0);
            }
        )";

    // Fragment Shader Source
    const char* fragmentSrcVertexColorMaterial = R"(
            #version 330 core

            in vec4 i_color;
            out vec4 frag_color;

            void main() {
                frag_color = i_color;
            }
        )";

    VertexColorMaterial::VertexColorMaterial()
            : shader(vertexSrcVertexColorMaterial, fragmentSrcVertexColorMaterial) {}

    void VertexColorMaterial::bind() const {
        shader.bind();
    }

    void VertexColorMaterial::unbind() const {
        shader.unbind();
    }

    const Shader &VertexColorMaterial::getShader() const {
        return shader;
    }

    VertexLayout VertexColorMaterial::getRequiredVertexLayout() const {
        return VertexLayout::PositionColor;
    }

}