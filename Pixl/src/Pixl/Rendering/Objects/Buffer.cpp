//
// Created by ChiroYuki on 01/08/2025.
//

#include "Pixl/Rendering/Objects/Buffer.h"

namespace Pixl {

    // ------------ [ VertexBuffer ] ------------ //

    VertexBuffer::VertexBuffer(uint32_t size, BufferUsage usage)
            : m_size(size), m_usage(usage) {
        glGenBuffers(1, &m_rendererID);
        glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
        glBufferData(GL_ARRAY_BUFFER, size, nullptr, static_cast<GLenum>(usage));
    }

    VertexBuffer::VertexBuffer(const void* vertices, uint32_t size, BufferUsage usage)
            : m_size(size), m_usage(usage) {
        glGenBuffers(1, &m_rendererID);
        glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, static_cast<GLenum>(usage));
    }

    VertexBuffer::~VertexBuffer() {
        if (m_rendererID) {
            glDeleteBuffers(1, &m_rendererID);
        }
    }

    VertexBuffer::VertexBuffer(VertexBuffer&& other) noexcept
            : m_rendererID(other.m_rendererID), m_size(other.m_size), m_usage(other.m_usage) {
        other.m_rendererID = 0;
        other.m_size = 0;
    }

    VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other) noexcept {
        if (this != &other) {
            if (m_rendererID) {
                glDeleteBuffers(1, &m_rendererID);
            }
            m_rendererID = other.m_rendererID;
            m_size = other.m_size;
            m_usage = other.m_usage;
            other.m_rendererID = 0;
            other.m_size = 0;
        }
        return *this;
    }

    void VertexBuffer::bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
    }

    void VertexBuffer::unbind() const {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void VertexBuffer::setData(const void* data, uint32_t size) {
        bind();
        if (size <= m_size) {
            glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
        } else {
            glBufferData(GL_ARRAY_BUFFER, size, data, static_cast<GLenum>(m_usage));
            m_size = size;
        }
    }

    void VertexBuffer::setSubData(const void* data, uint32_t size, uint32_t offset) {
        bind();
        glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
    }

    // ------------ [ IndexBuffer ] ------------ //

    IndexBuffer::IndexBuffer(const uint32_t* indices, uint32_t count, BufferUsage usage)
            : m_count(count) {
        glGenBuffers(1, &m_rendererID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, static_cast<GLenum>(usage));
    }

    IndexBuffer::~IndexBuffer() {
        if (m_rendererID) {
            glDeleteBuffers(1, &m_rendererID);
        }
    }

    IndexBuffer::IndexBuffer(IndexBuffer&& other) noexcept
            : m_rendererID(other.m_rendererID), m_count(other.m_count) {
        other.m_rendererID = 0;
        other.m_count = 0;
    }

    IndexBuffer& IndexBuffer::operator=(IndexBuffer&& other) noexcept {
        if (this != &other) {
            if (m_rendererID) {
                glDeleteBuffers(1, &m_rendererID);
            }
            m_rendererID = other.m_rendererID;
            m_count = other.m_count;
            other.m_rendererID = 0;
            other.m_count = 0;
        }
        return *this;
    }

    void IndexBuffer::bind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
    }

    void IndexBuffer::unbind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

}