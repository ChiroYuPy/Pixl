#ifndef PIXLENGINE_VERTEXARRAY_H
#define PIXLENGINE_VERTEXARRAY_H

#include "glad/glad.h"
#include "Pixl/Core/Base.h"
#include "Buffer.h"
#include "VertexDeclaration.h"

namespace Pixl {

    class VertexArray {
    public:
        VertexArray();
        ~VertexArray();

        void bind() const;
        void unbind() const;

        void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer, const VertexDeclaration& declaration);
        void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer);

        const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; }
        const Ref<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }

    private:
        uint32_t CalculateStride(const std::vector<VertexDeclarationComponent>& components);
        uint32_t GetComponentCount(VertexAttributeType type);
        GLenum ShaderDataTypeToOpenGLBaseType(VertexAttributeType type);

        uint32_t m_RendererID;
        uint32_t m_VertexBufferIndex = 0;
        std::vector<Ref<VertexBuffer>> m_VertexBuffers;
        Ref<IndexBuffer> m_IndexBuffer;
    };

}

#endif //PIXLENGINE_VERTEXARRAY_H