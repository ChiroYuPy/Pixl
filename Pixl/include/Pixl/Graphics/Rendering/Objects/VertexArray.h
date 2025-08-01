//
// Created by ChiroYuki on 01/08/2025.
//

#ifndef PIXLENGINE_VERTEXARRAY_H
#define PIXLENGINE_VERTEXARRAY_H

#include <vector>
#include "glad/glad.h"

#include "Buffer.h"
#include "Pixl/Core/Base.h"

namespace Pixl {

    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
    {
        switch (type)
        {
            case ShaderDataType::Float:    return GL_FLOAT;
            case ShaderDataType::Float2:   return GL_FLOAT;
            case ShaderDataType::Float3:   return GL_FLOAT;
            case ShaderDataType::Float4:   return GL_FLOAT;
            case ShaderDataType::Mat3:     return GL_FLOAT;
            case ShaderDataType::Mat4:     return GL_FLOAT;
            case ShaderDataType::Int:      return GL_INT;
            case ShaderDataType::Int2:     return GL_INT;
            case ShaderDataType::Int3:     return GL_INT;
            case ShaderDataType::Int4:     return GL_INT;
            case ShaderDataType::Bool:     return GL_BOOL;
            case ShaderDataType::None:     break;
        }
        return 0;
    }

    class VertexArray {
    public:
        VertexArray();

        virtual ~VertexArray();

        virtual void bind() const;

        virtual void Unbind() const;

        virtual void AddVertexBuffer(const Ref<VertexBuffer> &vertexBuffer);

        virtual void SetIndexBuffer(const Ref<IndexBuffer> &indexBuffer);

        virtual const std::vector<Ref<VertexBuffer>> &GetVertexBuffers() const { return m_VertexBuffers; }

        virtual const Ref<IndexBuffer> &GetIndexBuffer() const { return m_IndexBuffer; }

    private:
        uint32_t m_RendererID;
        uint32_t m_VertexBufferIndex = 0;
        std::vector<Ref<VertexBuffer>> m_VertexBuffers;
        Ref<IndexBuffer> m_IndexBuffer;
    };

}

#endif //PIXLENGINE_VERTEXARRAY_H
