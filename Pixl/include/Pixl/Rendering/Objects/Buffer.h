//
// Created by ChiroYuki on 01/08/2025.
//

#ifndef PIXLENGINE_BUFFER_H
#define PIXLENGINE_BUFFER_H

#include "Pixl/Core/Base.h"

#include <glad/glad.h>

namespace Pixl {

    enum class BufferUsage {
        Static = GL_STATIC_DRAW,
        Dynamic = GL_DYNAMIC_DRAW,
        Stream = GL_STREAM_DRAW
    };

    class VertexBuffer {
    public:
        VertexBuffer(uint32_t size, BufferUsage usage = BufferUsage::Dynamic);
        VertexBuffer(const void* vertices, uint32_t size, BufferUsage usage = BufferUsage::Static);
        ~VertexBuffer();

        // Non-copiable mais déplaçable
        VertexBuffer(const VertexBuffer&) = delete;
        VertexBuffer& operator=(const VertexBuffer&) = delete;
        VertexBuffer(VertexBuffer&& other) noexcept;
        VertexBuffer& operator=(VertexBuffer&& other) noexcept;

        void bind() const;
        void unbind() const;

        void setData(const void* data, uint32_t size);
        void setSubData(const void* data, uint32_t size, uint32_t offset = 0);

        uint32_t getSize() const { return m_size; }
        GL_ID getID() const { return m_rendererID; }

    private:
        GL_ID m_rendererID = 0;
        uint32_t m_size = 0;
        BufferUsage m_usage;
    };

    class IndexBuffer {
    public:
        IndexBuffer(const uint32_t* indices, uint32_t count, BufferUsage usage = BufferUsage::Static);
        ~IndexBuffer();

        // Non-copiable mais déplaçable
        IndexBuffer(const IndexBuffer&) = delete;
        IndexBuffer& operator=(const IndexBuffer&) = delete;
        IndexBuffer(IndexBuffer&& other) noexcept;
        IndexBuffer& operator=(IndexBuffer&& other) noexcept;

        void bind() const;
        void unbind() const;

        uint32_t getCount() const { return m_count; }
        GL_ID getID() const { return m_rendererID; }

    private:
        GL_ID m_rendererID = 0;
        uint32_t m_count = 0;
    };

}

#endif //PIXLENGINE_BUFFER_H
