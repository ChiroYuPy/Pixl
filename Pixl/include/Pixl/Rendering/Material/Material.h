//
// Created by ChiroYuki on 02/08/2025.
//

#ifndef PIXLENGINE_MATERIAL_H
#define PIXLENGINE_MATERIAL_H

#include "Pixl/Rendering/Objects/Shader.h"
#include "Pixl/Rendering/Objects/ShaderReflection.h"
#include <unordered_map>

namespace Pixl {

    class Material {
    public:
        explicit Material(Ref<Shader> shader);
        virtual ~Material() = default;

        void bind() const;
        void unbind() const;

        Ref<Shader> getShader() const { return m_shader; }
        const ShaderReflection& getReflection() const { return *m_reflection; }

        // Setters génériques avec vérification de type
        template<typename T>
        bool setProperty(const std::string& name, const T& value);

        // Getters
        template<typename T>
        bool getProperty(const std::string& name, T& outValue) const;

        // Vérifications
        bool hasProperty(const std::string& name) const;
        UniformType getPropertyType(const std::string& name) const;

        // Méthodes utilitaires
        std::vector<std::string> getPropertyNames() const;
        void resetToDefaults();

        // Pour debug/édition
        void printProperties() const;

    private:
        void applyProperty(const std::string& name, const UniformValue& value) const;

        Ref<Shader> m_shader;
        Scope<ShaderReflection> m_reflection;
        std::unordered_map<std::string, UniformValue> m_properties;
    };

    class MaterialFactory {
    public:
        static Ref<Material> create(Ref<Shader> shader);
        static Ref<Material> createFromFile(const std::string& vertexPath, const std::string& fragmentPath);
        static Ref<Material> createFromSource(const std::string& vertexSource, const std::string& fragmentSource);
    };

}

namespace Pixl {

    template<typename T>
    bool Material::setProperty(const std::string& name, const T& value) {
        const auto* uniformInfo = m_reflection->getUniform(name);
        if (!uniformInfo) {
            return false; // Uniform n'existe pas
        }

        // Vérification de compatibilité de type (simplifié)
        UniformValue uniformValue;
        try {
            uniformValue = value;
        } catch (...) {
            return false; // Type incompatible
        }

        m_properties[name] = uniformValue;
        return true;
    }

    template<typename T>
    bool Material::getProperty(const std::string& name, T& outValue) const {
        auto it = m_properties.find(name);
        if (it == m_properties.end()) {
            return false;
        }

        try {
            outValue = std::get<T>(it->second);
            return true;
        } catch (...) {
            return false;
        }
    }

}

#endif //PIXLENGINE_MATERIAL_H
