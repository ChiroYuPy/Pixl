//
// Created by ChiroYuki on 05/08/2025.
//

#include "Pixl/Rendering/Material/Material.h"
#include "Pixl/Utils/Logger.h"
#include <iostream>

namespace Pixl {

    Material::Material(Ref<Shader> shader)
            : m_shader(std::move(shader)) {

        if (!m_shader || !m_shader->isValid()) {
            Logger::error("Material: Invalid shader provided");
            return;
        }
    }

    void Material::bind() const {
        if (!m_shader) return;
        m_shader->bind();
    }

    void Material::unbind() const {
        if (!m_shader) return;
        m_shader->unbind();
    }

    Ref<Material> MaterialFactory::createSolidColor(const glm::vec3 color) {
        auto shader = MakeRef<Shader>();

        const std::string vertexSource = R"(
        #version 330 core

        layout(location = 0) in vec3 a_position;

        uniform mat4 u_viewProjection;
        uniform mat4 u_transform;

        void main() {
            gl_Position = u_viewProjection * u_transform * vec4(a_position, 1.0);
        }
        )";

        const std::string fragmentSource = R"(
        #version 330 core

        out vec4 frag_color;

        uniform vec3 u_color;

        void main() {
            frag_color = vec4(u_color, 1.0);
        }
        )";

        if (!shader->loadFromSource(vertexSource, fragmentSource)) {
            Logger::error("Failed to load shader from source");
            return nullptr;
        }

        shader->bind();
        shader->setFloat3("u_color", color);
        return MakeRef<Material>(std::move(shader));
    }

}