//
// Created by ChiroYuki on 01/08/2025.
//

#ifndef PIXLENGINE_SHADER_H
#define PIXLENGINE_SHADER_H

#include "Pixl/Core/Base.h"

#include <unordered_map>
#include <string>
#include <glm/glm.hpp>
#include <glad/glad.h>

namespace Pixl {

    class Shader {
    public:
        Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
        ~Shader();

        void bind() const;
        void unbind() const;

        void setInt(const std::string& name, int value);
        void setInt2(const std::string &name, const glm::ivec2 &value);
        void setInt3(const std::string &name, const glm::ivec3 &value);
        void setInt4(const std::string &name, const glm::ivec4 &value);
        void setIntArray(const std::string &name, int *values, uint32_t count);

        void setUInt(const std::string &name, uint32_t value);
        void setUInt2(const std::string &name, const glm::uvec2 &value);
        void setUInt3(const std::string &name, const glm::uvec3 &value);
        void setUInt4(const std::string &name, const glm::uvec4 &value);

        void setFloat(const std::string& name, float value);
        void setFloat2(const std::string& name, const glm::vec2& value);
        void setFloat3(const std::string& name, const glm::vec3& value);
        void setFloat4(const std::string& name, const glm::vec4& value);

        void setMat3(const std::string &name, const glm::mat3 &matrix);
        void setMat4(const std::string& name, const glm::mat4& matrix);

        GL_ID getRendererID() const { return m_RendererID; }

    private:
        GL_ID CompileShader(uint32_t type, const std::string& source);
        GL_ID m_RendererID;
        std::unordered_map<std::string, int> m_UniformLocationCache;

        int getUniformLocation(const std::string& name);
    };

}

#endif //PIXLENGINE_SHADER_H
