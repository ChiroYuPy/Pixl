#ifndef PIXLENGINE_VERTEXARRAY_H
#define PIXLENGINE_VERTEXARRAY_H

#include "Pixl/Core/Base.h"
#include "Pixl/Rendering/Objects/Buffer.h"
#include "Pixl/Rendering/Objects/VertexLayout.h"

namespace Pixl {

    class VertexArray {
    public:
        VertexArray();
        ~VertexArray();

        // Non-copiable mais déplaçable
        VertexArray(const VertexArray&) = delete;
        VertexArray& operator=(const VertexArray&) = delete;
        VertexArray(VertexArray&& other) noexcept;
        VertexArray& operator=(VertexArray&& other) noexcept;

        void bind() const;
        static void unbind();

        void addVertexBuffer(const Ref<VertexBuffer>& vertexBuffer, const VertexLayout& layout);
        void setIndexBuffer(const Ref<IndexBuffer>& indexBuffer);

        const std::vector<Ref<VertexBuffer>>& getVertexBuffers() const { return m_vertexBuffers; }
        const Ref<IndexBuffer>& getIndexBuffer() const { return m_indexBuffer; }

        bool hasIndexBuffer() const { return m_indexBuffer != nullptr; }
        uint32_t getIndexCount() const { return m_indexBuffer ? m_indexBuffer->getCount() : 0; }

    private:
        static void setupVertexAttributes(const VertexLayout& layout, uint32_t bufferIndex);

        GL_ID m_rendererID;
        uint32_t m_vertexBufferIndex;
        std::vector<Ref<VertexBuffer>> m_vertexBuffers;
        Ref<IndexBuffer> m_indexBuffer;
    };

}

#endif //PIXLENGINE_VERTEXARRAY_H