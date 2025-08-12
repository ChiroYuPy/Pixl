//
// Created by ChiroYuki on 05/08/2025.
//

#ifndef PIXLENGINE_VERTEXFORMAT_H
#define PIXLENGINE_VERTEXFORMAT_H

#include <string>
#include <cstdint>
#include <utility>
#include <vector>

#include <glad/glad.h>

namespace Pixl {

    enum class VertexAttributeType {
        Float, Float2, Float3, Float4,
        Int, Int2, Int3, Int4
    };

    inline int getAttributeComponentCount(VertexAttributeType type) {
        switch (type) {
            case VertexAttributeType::Float: return 1;
            case VertexAttributeType::Float2: return 2;
            case VertexAttributeType::Float3: return 3;
            case VertexAttributeType::Float4: return 4;
            case VertexAttributeType::Int: return 1;
            case VertexAttributeType::Int2: return 2;
            case VertexAttributeType::Int3: return 3;
            case VertexAttributeType::Int4: return 4;
        }
        return 0;
    }

    inline GLenum getAttributeGLType(VertexAttributeType type) {
        switch (type) {
            case VertexAttributeType::Float:
            case VertexAttributeType::Float2:
            case VertexAttributeType::Float3:
            case VertexAttributeType::Float4:
                return GL_FLOAT;
            case VertexAttributeType::Int:
            case VertexAttributeType::Int2:
            case VertexAttributeType::Int3:
            case VertexAttributeType::Int4:
                return GL_INT;
        }
        return GL_FLOAT;
    }

    inline size_t getAttributeSize(VertexAttributeType type) {
        int components = getAttributeComponentCount(type);
        GLenum glType = getAttributeGLType(type);
        size_t typeSize = (glType == GL_FLOAT) ? sizeof(float) : sizeof(int);
        return components * typeSize;
    }

    struct VertexAttribute {
        VertexAttributeType type;
        unsigned int location;
        size_t offset;
        bool normalized;

        VertexAttribute(VertexAttributeType t, unsigned int loc, size_t off, bool norm = false)
                : type(t), location(loc), offset(off), normalized(norm) {}
    };

    class VertexFormat {
    public:
        VertexFormat() : m_stride(0) {}

        VertexFormat& addAttribute(VertexAttributeType type, unsigned int location, size_t offset, bool normalized = false) {
            m_attributes.emplace_back(type, location, offset, normalized);
            size_t end = offset + getAttributeSize(type);
            if (end > m_stride) m_stride = end;
            return *this;
        }

        size_t getStride() const {
            return m_stride;
        }

        const std::vector<VertexAttribute>& getAttributes() const {
            return m_attributes;
        }

        void applyToVAO(bool instanced = false, unsigned int divisor = 1) const {
            for (const auto& attr : m_attributes) {
                glEnableVertexAttribArray(attr.location);
                GLenum glType = getAttributeGLType(attr.type);
                int components = getAttributeComponentCount(attr.type);

                if (glType == GL_FLOAT) {
                    glVertexAttribPointer(attr.location, components, glType,
                                          attr.normalized ? GL_TRUE : GL_FALSE,
                                          static_cast<GLsizei>(m_stride),
                                          reinterpret_cast<const void*>(attr.offset));
                } else {
                    glVertexAttribIPointer(attr.location, components, glType,
                                           static_cast<GLsizei>(m_stride),
                                           reinterpret_cast<const void*>(attr.offset));
                }

                if (instanced)
                    glVertexAttribDivisor(attr.location, divisor);
            }
        }

    private:
        std::vector<VertexAttribute> m_attributes;
        size_t m_stride;
    };

}

#endif //PIXLENGINE_VERTEXFORMAT_H
