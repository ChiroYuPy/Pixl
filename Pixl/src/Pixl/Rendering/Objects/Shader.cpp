//
// Created by ChiroYuki on 01/08/2025.
//

#include "Pixl/Rendering/Objects/Shader.h"
#include "Pixl/Utils/Logger.h"

#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/gtc/type_ptr.hpp>

namespace Pixl {

    Shader::~Shader() {
        if (m_rendererID)
            glDeleteProgram(m_rendererID);
    }

    Shader::Shader(Shader&& other) noexcept {
        m_rendererID = other.m_rendererID;
        m_uniformLocationCache = std::move(other.m_uniformLocationCache);
        other.m_rendererID = 0;
    }

    Shader& Shader::operator=(Shader&& other) noexcept {
        if (this != &other) {
            if (m_rendererID)
                glDeleteProgram(m_rendererID);
            m_rendererID = other.m_rendererID;
            m_uniformLocationCache = std::move(other.m_uniformLocationCache);
            other.m_rendererID = 0;
        }
        return *this;
    }

    bool Shader::loadFromSource(const std::string& vertexSource, const std::string& fragmentSource) {
        uint32_t vertexShader = compileShader(GL_VERTEX_SHADER, vertexSource);
        uint32_t fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSource);

        if (vertexShader == 0 || fragmentShader == 0) {
            if (vertexShader) glDeleteShader(vertexShader);
            if (fragmentShader) glDeleteShader(fragmentShader);
            return false;
        }

        if (m_rendererID)
            glDeleteProgram(m_rendererID);

        m_rendererID = glCreateProgram();
        glAttachShader(m_rendererID, vertexShader);
        glAttachShader(m_rendererID, fragmentShader);
        glLinkProgram(m_rendererID);

        int success;
        glGetProgramiv(m_rendererID, GL_LINK_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetProgramInfoLog(m_rendererID, 512, nullptr, infoLog);
            std::cerr << "Shader linking failed:\n" << infoLog << std::endl;
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
            return false;
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return true;
    }

    bool Shader::loadFromFile(const std::string& vertexPath, const std::string& fragmentPath) {
        std::ifstream vertexFile(vertexPath);
        std::ifstream fragmentFile(fragmentPath);

        if (!vertexFile || !fragmentFile) {
            std::cerr << "Failed to open shader file(s):\n"
                      << "Vertex: " << vertexPath << "\n"
                      << "Fragment: " << fragmentPath << std::endl;
            return false;
        }

        std::stringstream vertexBuffer, fragmentBuffer;
        vertexBuffer << vertexFile.rdbuf();
        fragmentBuffer << fragmentFile.rdbuf();

        return loadFromSource(vertexBuffer.str(), fragmentBuffer.str());
    }

    void Shader::bind() const {
        glUseProgram(m_rendererID);

    }

    void Shader::unbind() const {
        glUseProgram(0);
    }

    uint32_t Shader::compileShader(uint32_t type, const std::string& source) {
        uint32_t id = glCreateShader(type);
        const char* src = source.c_str();
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        int success;
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetShaderInfoLog(id, 512, nullptr, infoLog);
            std::cerr << "Shader compilation error ("
                      << (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT")
                      << "): " << infoLog << std::endl;
            glDeleteShader(id);
            return 0;
        }

        return id;
    }

    int Shader::getUniformLocation(const std::string& name) const {
        if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
            return m_uniformLocationCache[name];

        int location = glGetUniformLocation(m_rendererID, name.c_str());
        if (location == -1)
            std::cerr << "Warning: uniform '" << name << "' doesn't exist or is unused in shader.\n";

        m_uniformLocationCache[name] = location;
        return location;
    }

    // ------------ [ Uniform setters ] ------------ //

    void Shader::setInt(const std::string& name, int value) const {
        glUniform1i(getUniformLocation(name), value);
    }

    void Shader::setInt2(const std::string& name, const glm::ivec2& value) const {
        glUniform2i(getUniformLocation(name), value.x, value.y);
    }

    void Shader::setInt3(const std::string& name, const glm::ivec3& value) const {
        glUniform3i(getUniformLocation(name), value.x, value.y, value.z);
    }

    void Shader::setInt4(const std::string& name, const glm::ivec4& value) const {
        glUniform4i(getUniformLocation(name), value.x, value.y, value.z, value.w);
    }

    void Shader::setUInt(const std::string& name, uint32_t value) const {
        glUniform1ui(getUniformLocation(name), value);
    }

    void Shader::setUInt2(const std::string& name, const glm::uvec2& value) const {
        glUniform2ui(getUniformLocation(name), value.x, value.y);
    }

    void Shader::setUInt3(const std::string& name, const glm::uvec3& value) const {
        glUniform3ui(getUniformLocation(name), value.x, value.y, value.z);
    }

    void Shader::setUInt4(const std::string& name, const glm::uvec4& value) const {
        glUniform4ui(getUniformLocation(name), value.x, value.y, value.z, value.w);
    }

    void Shader::setIntArray(const std::string& name, int* values, uint32_t count) const {
        glUniform1iv(getUniformLocation(name), static_cast<GLsizei>(count), values);
    }

    void Shader::setFloat(const std::string& name, float value) const {
        glUniform1f(getUniformLocation(name), value);
    }

    void Shader::setFloat2(const std::string& name, const glm::vec2& value) const {
        glUniform2f(getUniformLocation(name), value.x, value.y);
    }

    void Shader::setFloat3(const std::string& name, const glm::vec3& value) const {
        glUniform3f(getUniformLocation(name), value.x, value.y, value.z);
    }

    void Shader::setFloat4(const std::string& name, const glm::vec4& value) const {
        glUniform4f(getUniformLocation(name), value.x, value.y, value.z, value.w);
    }

    void Shader::setMat3(const std::string& name, const glm::mat3& matrix) const {
        glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void Shader::setMat4(const std::string& name, const glm::mat4& matrix) const {
        glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
    }

}
