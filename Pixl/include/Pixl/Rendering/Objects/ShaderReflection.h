//
// Created by ChiroYuki on 05/08/2025.
//

#ifndef PIXLENGINE_SHADERREFLECTION_H
#define PIXLENGINE_SHADERREFLECTION_H

#include "Pixl/Core/Base.h"

#include <string>
#include <unordered_map>
#include <variant>
#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>

namespace Pixl {

    enum class UniformType {
        None = 0,
        Float, Float2, Float3, Float4,
        Int, Int2, Int3, Int4,
        UInt, UInt2, UInt3, UInt4,
        Mat3, Mat4,
        Bool,
        Sampler2D, SamplerCube
    };

    // Type variant pour stocker les valeurs des uniformes
    using UniformValue = std::variant<
            float, glm::vec2, glm::vec3, glm::vec4,
            int, glm::ivec2, glm::ivec3, glm::ivec4,
            uint32_t, glm::uvec2, glm::uvec3, glm::uvec4,
            glm::mat3, glm::mat4,
            bool
    >;

    struct UniformInfo {
        std::string name;
        UniformType type;
        int location;
        int size;  // Pour les arrays
        UniformValue defaultValue;
    };

    class ShaderReflection {
    public:
        explicit ShaderReflection(GL_ID shaderID);

        void introspect();

        const std::unordered_map<std::string, UniformInfo>& getUniforms() const { return m_uniforms; }
        bool hasUniform(const std::string& name) const;
        const UniformInfo* getUniform(const std::string& name) const;

        // Méthodes utilitaires
        std::vector<std::string> getUniformNames() const;
        std::vector<UniformInfo> getUniformsOfType(UniformType type) const;

    private:
        UniformType glTypeToUniformType(GLenum glType) const;
        UniformValue getDefaultValueForType(UniformType type) const;

        GL_ID m_shaderID;
        std::unordered_map<std::string, UniformInfo> m_uniforms;
    };

}
#endif //PIXLENGINE_SHADERREFLECTION_H
