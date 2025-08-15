//
// Created by ChiroYuki on 05/08/2025.
//

#include "Pixl/Rendering/Material/Material.h"
#include "Pixl/Utils/Logger.h"
#include "Pixl/Core/Application.h"
#include <iostream>
#include <utility>

namespace Pixl {

    Material::Material(Ref<Shader> shader)
            : m_shader(std::move(shader)) {

        if (!m_shader || !m_shader->isValid()) {
            Logger::error("Material: Invalid shader provided");
            return;
        }
    }

    void Material::bind() const {
        if (!m_shader) {
            Logger::warn("Material::bind: No shader to use");
            return;
        }

        for (const auto& [name, value] : m_floatValues)
            m_shader->setFloat(name, value);

        for (const auto& [name, value] : m_vec2Values)
            m_shader->setFloat2(name, value);

        for (const auto& [name, value] : m_vec3Values)
            m_shader->setFloat3(name, value);

        for (const auto& [name, value] : m_vec4Values)
            m_shader->setFloat4(name, value);

        for (const auto& [name, value] : m_mat3Values)
            m_shader->setMat3(name, value);

        for (const auto& [name, value] : m_mat4Values)
            m_shader->setMat4(name, value);

        for (const auto& [name, value] : m_intValues)
            m_shader->setInt(name, value);

        for (const auto& [name, texSlot] : m_textures) {
            if (texSlot.texture) {
                texSlot.texture->bind(texSlot.slot);
                m_shader->setInt(name, texSlot.slot);
            }
        }
    }

    void Material::unbind() const {
        if (!m_shader) return;
        m_shader->unbind();
    }

    void Material::cleanup() {
        m_floatValues.clear();
        m_vec2Values.clear();
        m_vec3Values.clear();
        m_vec4Values.clear();
        m_mat3Values.clear();
        m_mat4Values.clear();
        m_intValues.clear();
        m_textures.clear();
        m_shader.reset();
    }

    Ref<Material> MaterialFactory::createSolidColor(const glm::vec3& color) {
        auto& resourceService = Application::get().getResourceService();

        auto shaderOpt = resourceService.getShader("shaders/ColorUnlitShader.json");
        if (!shaderOpt.has_value()) {
            Logger::error("MaterialFactory::createSolidColor: Failed to load ColorUnlitShader");
            return nullptr;
        }

        auto material = MakeRef<Material>(shaderOpt.value());
        if (!material || !material->getShader()) {
            Logger::error("MaterialFactory::createSolidColor: Failed to create material");
            return nullptr;
        }

        material->bind();
        material->setFloat3("u_color", color);
        material->unbind();

        return material;
    }

    Ref<Material> MaterialFactory::createTextured(Ref<Texture> texture, const glm::vec3& tint) {
        auto& resourceService = Application::get().getResourceService();

        auto shaderOpt = resourceService.getShader("shaders/TexturedShader.json");
        if (!shaderOpt.has_value()) {
            Logger::error("MaterialFactory::createTextured: Failed to load TexturedShader");
            return nullptr;
        }

        auto material = MakeRef<Material>(shaderOpt.value());
        if (!material || !material->getShader()) {
            Logger::error("MaterialFactory::createTextured: Failed to create material");
            return nullptr;
        }

        material->bind();
        material->setTexture("u_texture", texture, 0);
        material->setFloat3("u_tint", tint);
        material->unbind();

        return material;
    }

}