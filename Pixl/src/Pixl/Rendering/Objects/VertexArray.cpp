//
// Created by ChiroYuki on 01/08/2025.
//

#include "Pixl/Rendering/Objects/VertexArray.h"

namespace Pixl {

    VertexArray::VertexArray() : m_RendererID() {
        glGenVertexArrays(1, &m_RendererID);
    }

    VertexArray::~VertexArray() {
        glDeleteVertexArrays(1, &m_RendererID);
    }

    void VertexArray::bind() const {
        glBindVertexArray(m_RendererID);
    }

    void VertexArray::unbind() const {
        glBindVertexArray(0);
    }

    void VertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer, const VertexDeclaration& declaration) {
        glBindVertexArray(m_RendererID);
        vertexBuffer->bind();

        const auto& components = declaration.GetComponents();
        uint32_t stride = CalculateStride(components);
        size_t offset = 0;

        for (const auto& component : components) {
            uint32_t componentSize = ShaderDataTypeSize(component.type);

            switch (component.type) {
                case ComponentType::Float:
                case ComponentType::Float2:
                case ComponentType::Float3:
                case ComponentType::Float4: {
                    glEnableVertexAttribArray(m_VertexBufferIndex);
                    glVertexAttribPointer(m_VertexBufferIndex,
                                          GetComponentCount(component.type),
                                          ShaderDataTypeToOpenGLBaseType(component.type),
                                          GL_FALSE, // normalized
                                          stride,
                                          reinterpret_cast<const void*>(offset));
                    m_VertexBufferIndex++;
                    break;
                }
                case ComponentType::Int:
                case ComponentType::Int2:
                case ComponentType::Int3:
                case ComponentType::Int4:
                case ComponentType::Bool: {
                    glEnableVertexAttribArray(m_VertexBufferIndex);
                    glVertexAttribIPointer(m_VertexBufferIndex,
                                           GetComponentCount(component.type),
                                           ShaderDataTypeToOpenGLBaseType(component.type),
                                           stride,
                                           reinterpret_cast<const void*>(offset));
                    m_VertexBufferIndex++;
                    break;
                }
                case ComponentType::Mat3:
                case ComponentType::Mat4: {
                    uint8_t count = GetComponentCount(component.type);
                    for (uint8_t i = 0; i < count; i++) {
                        glEnableVertexAttribArray(m_VertexBufferIndex);
                        glVertexAttribPointer(m_VertexBufferIndex,
                                              count,
                                              ShaderDataTypeToOpenGLBaseType(component.type),
                                              GL_FALSE,
                                              stride,
                                              reinterpret_cast<const void*>(offset + sizeof(float) * count * i));
                        glVertexAttribDivisor(m_VertexBufferIndex, 1);
                        m_VertexBufferIndex++;
                    }
                    break;
                }
                default:
                    break;
            }

            offset += componentSize;
        }

        m_VertexBuffers.push_back(vertexBuffer);
    }

    void VertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) {
        glBindVertexArray(m_RendererID);
        indexBuffer->bind();

        m_IndexBuffer = indexBuffer;
    }

    uint32_t VertexArray::CalculateStride(const std::vector<VertexDeclarationComponent>& components) {
        uint32_t stride = 0;
        for (const auto& component : components) {
            stride += ShaderDataTypeSize(component.type);
        }
        return stride;
    }

    uint32_t VertexArray::GetComponentCount(ComponentType type) {
        switch (type) {
            case ComponentType::Float:    return 1;
            case ComponentType::Float2:   return 2;
            case ComponentType::Float3:   return 3;
            case ComponentType::Float4:   return 4;
            case ComponentType::Mat3:     return 3; // 3x3 matrix
            case ComponentType::Mat4:     return 4; // 4x4 matrix
            case ComponentType::Int:      return 1;
            case ComponentType::Int2:     return 2;
            case ComponentType::Int3:     return 3;
            case ComponentType::Int4:     return 4;
            case ComponentType::Bool:     return 1;
            default:                      return 0;
        }
    }

    GLenum VertexArray::ShaderDataTypeToOpenGLBaseType(ComponentType type) {
        switch (type) {
            case ComponentType::Float:
            case ComponentType::Float2:
            case ComponentType::Float3:
            case ComponentType::Float4:
            case ComponentType::Mat3:
            case ComponentType::Mat4:
                return GL_FLOAT;
            case ComponentType::Int:
            case ComponentType::Int2:
            case ComponentType::Int3:
            case ComponentType::Int4:
                return GL_INT;
            case ComponentType::Bool:
                return GL_BOOL;
            default:
                return 0;
        }
    }

}