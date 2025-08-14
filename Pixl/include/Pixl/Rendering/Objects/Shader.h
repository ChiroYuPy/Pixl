//
// Created by ChiroYuki on 01/08/2025.
//

#ifndef PIXLENGINE_SHADER_H
#define PIXLENGINE_SHADER_H

#include "Pixl/Core/Base.h"
#include "Pixl/Core/Resource/Resource.h"

#include <unordered_map>
#include <string>
#include <glm/glm.hpp>
#include <glad/glad.h>

namespace Pixl {

    class Shader : public IResource {
    public:
        Shader() = default;
        ~Shader();

        Shader(const Shader&) = delete;
        Shader& operator=(const Shader&) = delete;
        Shader(Shader&& other) noexcept;
        Shader& operator=(Shader&& other) noexcept;

        bool loadFromSource(const std::string& vertexSource, const std::string& fragmentSource);
        bool loadFromFile(const std::string& vertexPath, const std::string& fragmentPath);

        void bind() const;
        void unbind() const;

        void setInt(const std::string& name, int value) const;
        void setInt2(const std::string &name, const glm::ivec2 &value) const;
        void setInt3(const std::string &name, const glm::ivec3 &value) const;
        void setInt4(const std::string &name, const glm::ivec4 &value) const;
        void setIntArray(const std::string &name, int *values, uint32_t count) const;

        void setUInt(const std::string &name, uint32_t value) const;
        void setUInt2(const std::string &name, const glm::uvec2 &value) const;
        void setUInt3(const std::string &name, const glm::uvec3 &value) const;
        void setUInt4(const std::string &name, const glm::uvec4 &value) const;

        void setFloat(const std::string& name, float value) const;
        void setFloat2(const std::string& name, const glm::vec2& value) const;
        void setFloat3(const std::string& name, const glm::vec3& value) const;
        void setFloat4(const std::string& name, const glm::vec4& value) const;

        void setMat3(const std::string &name, const glm::mat3 &matrix) const;
        void setMat4(const std::string& name, const glm::mat4& matrix) const;

        GLint getID() const { return m_rendererID; }

        // Implémentation de IResource
        void cleanup() final;
        [[nodiscard]] bool isValid() const override;

    private:
        static uint32_t compileShader(uint32_t type, const std::string& source);
        int getUniformLocation(const std::string& name) const;

        GLint m_rendererID = 0;
        mutable std::unordered_map<std::string, int> m_uniformLocationCache;
    };

}

#endif //PIXLENGINE_SHADER_H
