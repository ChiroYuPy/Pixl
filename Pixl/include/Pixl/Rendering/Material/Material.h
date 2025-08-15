//
// Created by ChiroYuki on 02/08/2025.
//

#ifndef PIXLENGINE_MATERIAL_H
#define PIXLENGINE_MATERIAL_H

#include "Pixl/Rendering/Objects/Shader.h"
#include "Pixl/Rendering/Objects/Texture.h"
#include <unordered_map>

namespace Pixl {

    class Material : public IResource {
    public:
        explicit Material(Ref<Shader> shader);
        ~Material() = default;

        Material(const Material&) = delete;
        Material& operator=(const Material&) = delete;
        Material(Material&&) = default;
        Material& operator=(Material&&) = default;

        void bind() const;
        void unbind() const;

        Ref<Shader> getShader() const { return m_shader; }

        bool isValid() const override { return m_shader && m_shader->isValid(); }

        void setFloat(const std::string& name, float value) { m_floatValues[name] = value; }
        void setFloat2(const std::string& name, const glm::vec2& value) { m_vec2Values[name] = value; }
        void setFloat3(const std::string& name, const glm::vec3& value) { m_vec3Values[name] = value; }
        void setFloat4(const std::string& name, const glm::vec4& value) { m_vec4Values[name] = value; }

        void setMat3(const std::string& name, const glm::mat3& value) { m_mat3Values[name] = value; }
        void setMat4(const std::string& name, const glm::mat4& value) { m_mat4Values[name] = value; }

        void setInt(const std::string& name, int value) { m_intValues[name] = value; }
        void setTexture(const std::string& name, const Ref<Texture>& texture, int slot = 0) {
            m_textures[name] = { texture, slot };
        }

        void cleanup() override;


    private:
        Ref<Shader> m_shader;

        std::unordered_map<std::string, float> m_floatValues;
        std::unordered_map<std::string, glm::vec2> m_vec2Values;
        std::unordered_map<std::string, glm::vec3> m_vec3Values;
        std::unordered_map<std::string, glm::vec4> m_vec4Values;

        std::unordered_map<std::string, glm::mat3> m_mat3Values;
        std::unordered_map<std::string, glm::mat4> m_mat4Values;

        std::unordered_map<std::string, int> m_intValues;

        struct TextureSlot {
            Ref<Texture> texture;
            int slot;
        };
        std::unordered_map<std::string, TextureSlot> m_textures;
    };

    class MaterialFactory {
    public:
        static Ref<Material> createSolidColor(const glm::vec3& color = {1.0f, 0.0f, 0.0f});
        static Ref<Material> createTextured(Ref<Texture> texture, const glm::vec3& tint = {1.0f, 1.0f, 1.0f});
    };

}

namespace Pixl {

}

#endif //PIXLENGINE_MATERIAL_H
