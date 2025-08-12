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

    Ref<Material> MaterialFactory::createFromSource(const std::string& vertexSource,
                                                    const std::string& fragmentSource) {
        auto shader = MakeRef<Shader>();
        if (!shader->loadFromSource(vertexSource, fragmentSource)) {
            Logger::error("Failed to load shader from source");
            return nullptr;
        }
        return MakeRef<Material>(std::move(shader));
    }

}