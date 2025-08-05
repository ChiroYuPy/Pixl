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

        // Créer la réflexion
        m_reflection = MakeScope<ShaderReflection>(m_shader->getID());

        // Initialiser les propriétés avec les valeurs par défaut
        resetToDefaults();
    }

    void Material::bind() const {
        if (!m_shader) return;

        m_shader->bind();

        // Appliquer toutes les propriétés
        for (const auto& [name, value] : m_properties) {
            applyProperty(name, value);
        }
    }

    void Material::unbind() const {
        if (m_shader) {
            m_shader->unbind();
        }
    }

    bool Material::hasProperty(const std::string& name) const {
        return m_reflection->hasUniform(name);
    }

    UniformType Material::getPropertyType(const std::string& name) const {
        const auto* uniform = m_reflection->getUniform(name);
        return uniform ? uniform->type : UniformType::None;
    }

    std::vector<std::string> Material::getPropertyNames() const {
        return m_reflection->getUniformNames();
    }

    void Material::resetToDefaults() {
        const auto& uniforms = m_reflection->getUniforms();
        for (const auto& [name, info] : uniforms) {
            m_properties[name] = info.defaultValue;
        }
    }

    void Material::printProperties() const {
        std::cout << "Material Properties:\n";
        for (const auto& [name, value] : m_properties) {
            const auto* uniform = m_reflection->getUniform(name);
            if (uniform) {
                std::cout << "  " << name << " (type: " << static_cast<int>(uniform->type) << ")\n";
            }
        }
    }

    void Material::applyProperty(const std::string& name, const UniformValue& value) const {
        const auto* uniform = m_reflection->getUniform(name);
        if (!uniform) return;

        // Utiliser un visitor pattern pour appliquer la bonne méthode
        std::visit([this, &name](const auto& val) {
            using T = std::decay_t<decltype(val)>;

            if constexpr (std::is_same_v<T, float>) {
                m_shader->setFloat(name, val);
            } else if constexpr (std::is_same_v<T, glm::vec2>) {
                m_shader->setFloat2(name, val);
            } else if constexpr (std::is_same_v<T, glm::vec3>) {
                m_shader->setFloat3(name, val);
            } else if constexpr (std::is_same_v<T, glm::vec4>) {
                m_shader->setFloat4(name, val);
            } else if constexpr (std::is_same_v<T, int>) {
                m_shader->setInt(name, val);
            } else if constexpr (std::is_same_v<T, glm::ivec2>) {
                m_shader->setInt2(name, val);
            } else if constexpr (std::is_same_v<T, glm::ivec3>) {
                m_shader->setInt3(name, val);
            } else if constexpr (std::is_same_v<T, glm::ivec4>) {
                m_shader->setInt4(name, val);
            } else if constexpr (std::is_same_v<T, uint32_t>) {
                m_shader->setUInt(name, val);
            } else if constexpr (std::is_same_v<T, glm::uvec2>) {
                m_shader->setUInt2(name, val);
            } else if constexpr (std::is_same_v<T, glm::uvec3>) {
                m_shader->setUInt3(name, val);
            } else if constexpr (std::is_same_v<T, glm::uvec4>) {
                m_shader->setUInt4(name, val);
            } else if constexpr (std::is_same_v<T, glm::mat3>) {
                m_shader->setMat3(name, val);
            } else if constexpr (std::is_same_v<T, glm::mat4>) {
                m_shader->setMat4(name, val);
            } else if constexpr (std::is_same_v<T, bool>) {
                m_shader->setInt(name, val ? 1 : 0);
            }
        }, value);
    }

    // Factory implementation
    Ref<Material> MaterialFactory::create(Ref<Shader> shader) {
        return MakeRef<Material>(std::move(shader));
    }

    Ref<Material> MaterialFactory::createFromFile(const std::string& vertexPath,
                                                  const std::string& fragmentPath) {
        auto shader = MakeRef<Shader>();
        if (!shader->loadFromFile(vertexPath, fragmentPath)) {
            Logger::error("Failed to load shader from files: " + vertexPath + " and " + fragmentPath);
            return nullptr;
        }
        return create(shader);
    }

    Ref<Material> MaterialFactory::createFromSource(const std::string& vertexSource,
                                                    const std::string& fragmentSource) {
        auto shader = MakeRef<Shader>();
        if (!shader->loadFromSource(vertexSource, fragmentSource)) {
            Logger::error("Failed to load shader from source");
            return nullptr;
        }
        return create(shader);
    }

}