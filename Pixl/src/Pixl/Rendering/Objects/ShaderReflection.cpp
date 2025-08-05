//
// Created by ChiroYuki on 05/08/2025.
//

#include "Pixl/Rendering/Objects/ShaderReflection.h"
#include "Pixl/Utils/Logger.h"

namespace Pixl {

    ShaderReflection::ShaderReflection(GL_ID shaderID)
            : m_shaderID(shaderID) {
        introspect();
    }

    void ShaderReflection::introspect() {
        if (m_shaderID == 0) {
            Logger::error("ShaderReflection: Invalid shader ID");
            return;
        }

        GLint numUniforms = 0;
        glGetProgramiv(m_shaderID, GL_ACTIVE_UNIFORMS, &numUniforms);

        GLint maxNameLength = 0;
        glGetProgramiv(m_shaderID, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxNameLength);

        std::vector<char> nameBuffer(maxNameLength);

        for (int i = 0; i < numUniforms; ++i) {
            GLsizei nameLength = 0;
            GLint size = 0;
            GLenum type = 0;

            glGetActiveUniform(m_shaderID, i, maxNameLength, &nameLength,
                               &size, &type, nameBuffer.data());

            std::string uniformName(nameBuffer.data(), nameLength);

            // Skip les uniformes système OpenGL
            if (uniformName.find("gl_") == 0) {
                continue;
            }

            UniformInfo info;
            info.name = uniformName;
            info.type = glTypeToUniformType(type);
            info.location = glGetUniformLocation(m_shaderID, uniformName.c_str());
            info.size = size;
            info.defaultValue = getDefaultValueForType(info.type);

            m_uniforms[uniformName] = info;

            Logger::debug("Found uniform: " + uniformName +
                          " (type: " + std::to_string(static_cast<int>(info.type)) +
                          ", location: " + std::to_string(static_cast<int>(info.location)) + ")");
        }
    }

    bool ShaderReflection::hasUniform(const std::string& name) const {
        return m_uniforms.find(name) != m_uniforms.end();
    }

    const UniformInfo* ShaderReflection::getUniform(const std::string& name) const {
        auto it = m_uniforms.find(name);
        return (it != m_uniforms.end()) ? &it->second : nullptr;
    }

    std::vector<std::string> ShaderReflection::getUniformNames() const {
        std::vector<std::string> names;
        names.reserve(m_uniforms.size());
        for (const auto& pair : m_uniforms) {
            names.push_back(pair.first);
        }
        return names;
    }

    std::vector<UniformInfo> ShaderReflection::getUniformsOfType(UniformType type) const {
        std::vector<UniformInfo> uniforms;
        for (const auto& pair : m_uniforms) {
            if (pair.second.type == type) {
                uniforms.push_back(pair.second);
            }
        }
        return uniforms;
    }

    UniformType ShaderReflection::glTypeToUniformType(GLenum glType) const {
        switch (glType) {
            case GL_FLOAT:        return UniformType::Float;
            case GL_FLOAT_VEC2:   return UniformType::Float2;
            case GL_FLOAT_VEC3:   return UniformType::Float3;
            case GL_FLOAT_VEC4:   return UniformType::Float4;
            case GL_INT:          return UniformType::Int;
            case GL_INT_VEC2:     return UniformType::Int2;
            case GL_INT_VEC3:     return UniformType::Int3;
            case GL_INT_VEC4:     return UniformType::Int4;
            case GL_UNSIGNED_INT: return UniformType::UInt;
            case GL_UNSIGNED_INT_VEC2: return UniformType::UInt2;
            case GL_UNSIGNED_INT_VEC3: return UniformType::UInt3;
            case GL_UNSIGNED_INT_VEC4: return UniformType::UInt4;
            case GL_FLOAT_MAT3:   return UniformType::Mat3;
            case GL_FLOAT_MAT4:   return UniformType::Mat4;
            case GL_BOOL:         return UniformType::Bool;
            case GL_SAMPLER_2D:   return UniformType::Sampler2D;
            case GL_SAMPLER_CUBE: return UniformType::SamplerCube;
            default:
                Logger::warn(std::format("Unknown uniform type: {}", glType));
                return UniformType::None;
        }
    }

    UniformValue ShaderReflection::getDefaultValueForType(UniformType type) const {
        switch (type) {
            case UniformType::Float:    return 0.0f;
            case UniformType::Float2:   return glm::vec2(0.0f);
            case UniformType::Float3:   return glm::vec3(0.0f);
            case UniformType::Float4:   return glm::vec4(0.0f);
            case UniformType::Int:      return 0;
            case UniformType::Int2:     return glm::ivec2(0);
            case UniformType::Int3:     return glm::ivec3(0);
            case UniformType::Int4:     return glm::ivec4(0);
            case UniformType::UInt:     return 0u;
            case UniformType::UInt2:    return glm::uvec2(0u);
            case UniformType::UInt3:    return glm::uvec3(0u);
            case UniformType::UInt4:    return glm::uvec4(0u);
            case UniformType::Mat3:     return glm::mat3(1.0f);
            case UniformType::Mat4:     return glm::mat4(1.0f);
            case UniformType::Bool:     return false;
            default:                    return 0.0f;
        }
    }

}