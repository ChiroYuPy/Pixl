//
// Created by ChiroYuki on 02/08/2025.
//

#include "Pixl/Rendering/Material/UnlitMaterial.h"
#include "Pixl/Utils/Logger.h"

namespace Pixl {

    UnlitMaterial::UnlitMaterial(Ref<Shader> shader)
    : Material(std::move(shader)) {}

    void UnlitMaterial::setColor(const glm::vec4 &col) {
        m_color = col;
    }

    void UnlitMaterial::bind() const {
        Material::bind();
        m_shader->setFloat4("u_color", m_color);
        // Logger::debug(std::format("color({}, {}, {}, {})", m_color.r, m_color.g, m_color.b, m_color.a));
    }

}