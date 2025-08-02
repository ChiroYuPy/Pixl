//
// Created by ChiroYuki on 01/08/2025.
//

#include "Pixl/Rendering/Shader.h"

#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/gtc/type_ptr.hpp>

namespace Pixl {

    Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc) {
        uint32_t vertexShader = CompileShader(GL_VERTEX_SHADER, vertexSrc);
        uint32_t fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentSrc);

        m_RendererID = glCreateProgram();
        glAttachShader(m_RendererID, vertexShader);
        glAttachShader(m_RendererID, fragmentShader);
        glLinkProgram(m_RendererID);

        int success;
        glGetProgramiv(m_RendererID, GL_LINK_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetProgramInfoLog(m_RendererID, 512, nullptr, infoLog);
            std::cerr << "Shader linking failed: " << infoLog << std::endl;
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    Shader::~Shader() {
        glDeleteProgram(m_RendererID);
    }

    void Shader::bind() const {
        glUseProgram(m_RendererID);
    }

    void Shader::unbind() const {
        glUseProgram(0);
    }

    uint32_t Shader::CompileShader(uint32_t type, const std::string& source) {
        uint32_t id = glCreateShader(type);
        const char* src = source.c_str();
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        int success;
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetShaderInfoLog(id, 512, nullptr, infoLog);
            std::cerr << "Shader compilation error (" << (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT") << "): " << infoLog << std::endl;
        }

        return id;
    }

    int Shader::getUniformLocation(const std::string& name) {
        if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
            return m_UniformLocationCache[name];

        int location = glGetUniformLocation(m_RendererID, name.c_str());
        if (location == -1)
            std::cerr << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;

        m_UniformLocationCache[name] = location;
        return location;
    }

    void Shader::setInt(const std::string& name, int value) {
        GLint location = getUniformLocation(name);
        glUniform1i(location, value);
    }

    void Shader::setInt2(const std::string& name, const glm::ivec2& value) {
        GLint location = getUniformLocation(name);
        glUniform2i(location, value.x, value.y);
    }

    void Shader::setInt3(const std::string& name, const glm::ivec3& value) {
        GLint location = getUniformLocation(name);
        glUniform3i(location, value.x, value.y, value.z);
    }

    void Shader::setInt4(const std::string& name, const glm::ivec4& value) {
        GLint location = getUniformLocation(name);
        glUniform4i(location, value.x, value.y, value.z, value.w);
    }

    void Shader::setUInt(const std::string& name, uint32_t value) {
        GLint location = getUniformLocation(name);
        glUniform1ui(location, value);
    }

    void Shader::setUInt2(const std::string& name, const glm::uvec2& value) {
        GLint location = getUniformLocation(name);
        glUniform2ui(location, value.x, value.y);
    }

    void Shader::setUInt3(const std::string& name, const glm::uvec3& value) {
        GLint location = getUniformLocation(name);
        glUniform3ui(location, value.x, value.y, value.z);
    }

    void Shader::setUInt4(const std::string& name, const glm::uvec4& value) {
        GLint location = getUniformLocation(name);
        glUniform4ui(location, value.x, value.y, value.z, value.w);
    }

    void Shader::setIntArray(const std::string& name, int* values, uint32_t count) {
        GLint location = getUniformLocation(name);
        glUniform1iv(location, static_cast<GLsizei>(count), values);
    }

    void Shader::setFloat(const std::string& name, float value) {
        GLint location = getUniformLocation(name);
        glUniform1f(location, value);
    }

    void Shader::setFloat2(const std::string &name, const glm::vec2 &value) {
        GLint location = getUniformLocation(name);
        glUniform2f(location, value.x, value.y);
    }

    void Shader::setFloat3(const std::string& name, const glm::vec3& value) {
        GLint location = getUniformLocation(name);
        glUniform3f(location, value.x, value.y, value.z);
    }

    void Shader::setFloat4(const std::string& name, const glm::vec4& value) {
        GLint location = getUniformLocation(name);
        glUniform4f(location, value.x, value.y, value.z, value.w);
    }

    void Shader::setMat3(const std::string& name, const glm::mat3& matrix) {
        GLint location = getUniformLocation(name);
        glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void Shader::setMat4(const std::string& name, const glm::mat4& matrix) {
        GLint location = getUniformLocation(name);
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }

}
