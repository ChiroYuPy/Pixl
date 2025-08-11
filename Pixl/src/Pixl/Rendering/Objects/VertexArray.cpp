//
// Created by ChiroYuki on 01/08/2025.
//

#include "Pixl/Rendering/Objects/VertexArray.h"

namespace Pixl {

    VertexArray::VertexArray()
    : m_rendererID(0), m_vertexBufferIndex(0) {
        glGenVertexArrays(1, &m_rendererID);
    }

    VertexArray::~VertexArray() {
        if (m_rendererID) {
            glDeleteVertexArrays(1, &m_rendererID);
        }
    }

    VertexArray::VertexArray(VertexArray&& other) noexcept
            : m_rendererID(other.m_rendererID),
              m_vertexBufferIndex(other.m_vertexBufferIndex),
              m_vertexBuffers(std::move(other.m_vertexBuffers)),
              m_indexBuffer(std::move(other.m_indexBuffer)) {
        other.m_rendererID = 0;
        other.m_vertexBufferIndex = 0;
    }

    VertexArray& VertexArray::operator=(VertexArray&& other) noexcept {
        if (this != &other) {
            if (m_rendererID) {
                glDeleteVertexArrays(1, &m_rendererID);
            }
            m_rendererID = other.m_rendererID;
            m_vertexBufferIndex = other.m_vertexBufferIndex;
            m_vertexBuffers = std::move(other.m_vertexBuffers);
            m_indexBuffer = std::move(other.m_indexBuffer);
            other.m_rendererID = 0;
            other.m_vertexBufferIndex = 0;
        }
        return *this;
    }

    void VertexArray::bind() const {
        glBindVertexArray(m_rendererID);
    }

    void VertexArray::unbind() {
        glBindVertexArray(0);
    }

    void VertexArray::addVertexBuffer(const Ref<VertexBuffer>& vertexBuffer, const VertexLayout& layout) {
        bind();
        vertexBuffer->bind();

        setupVertexAttributes(layout, m_vertexBufferIndex);
        m_vertexBuffers.push_back(vertexBuffer);
        m_vertexBufferIndex++;

        unbind();
    }

    void VertexArray::setIndexBuffer(const Ref<IndexBuffer>& indexBuffer) {
        bind();
        indexBuffer->bind();
        m_indexBuffer = indexBuffer;
        unbind();
    }

    void VertexArray::setupVertexAttributes(const VertexLayout& layout, uint32_t bufferIndex) {
        const auto& attributes = layout.getAttributes();

        for (uint32_t i = 0; i < attributes.size(); ++i) {
            const auto& attr = attributes[i];

            constexpr uint32_t MAX_ATTRIBUTES_PER_BUFFER = 8; //TODO: replace arbitrary value
            uint32_t location = bufferIndex * MAX_ATTRIBUTES_PER_BUFFER + i;

            glEnableVertexAttribArray(location);
            glVertexAttribPointer(
                    location,
                    static_cast<GLint>(VertexLayout::getAttributeComponentCount(attr.type)),
                    VertexLayout::getAttributeGLType(attr.type),
                    attr.normalized ? GL_TRUE : GL_FALSE,
                    static_cast<GLsizei>(layout.getStride()),
                    reinterpret_cast<const void*>(static_cast<uintptr_t>(attr.offset))
            );
        }
    }

}
