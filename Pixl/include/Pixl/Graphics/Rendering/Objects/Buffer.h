//
// Created by ChiroYuki on 01/08/2025.
//

#ifndef PIXLENGINE_BUFFER_H
#define PIXLENGINE_BUFFER_H

#include <utility>
#include <vector>
#include <string>
#include "glad/glad.h"
#include "Pixl/Core/Base.h"

namespace Pixl {

    enum class ShaderDataType {
        None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
    };

    static uint32_t ShaderDataTypeSize(ShaderDataType type) {
        switch (type)
        {
            case ShaderDataType::Float:    return 4;
            case ShaderDataType::Float2:   return 4 * 2;
            case ShaderDataType::Float3:   return 4 * 3;
            case ShaderDataType::Float4:   return 4 * 4;
            case ShaderDataType::Mat3:     return 4 * 3 * 3;
            case ShaderDataType::Mat4:     return 4 * 4 * 4;
            case ShaderDataType::Int:      return 4;
            case ShaderDataType::Int2:     return 4 * 2;
            case ShaderDataType::Int3:     return 4 * 3;
            case ShaderDataType::Int4:     return 4 * 4;
            case ShaderDataType::Bool:     return 1;
            case ShaderDataType::None:     break;
        }

        return 0;
    }

    struct BufferElement {
        std::string Name;
        ShaderDataType Type;
        uint32_t Size{};
        size_t Offset{};
        bool Normalized{};

        BufferElement() = default;

        BufferElement(ShaderDataType type, std::string  name, bool normalized = false)
                : Name(std::move(name)), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
                {}

        uint32_t GetComponentCount() const {
            switch (Type)
            {
                case ShaderDataType::Float:   return 1;
                case ShaderDataType::Float2:  return 2;
                case ShaderDataType::Float3:  return 3;
                case ShaderDataType::Float4:  return 4;
                case ShaderDataType::Mat3:    return 3; // 3* float3
                case ShaderDataType::Mat4:    return 4; // 4* float4
                case ShaderDataType::Int:     return 1;
                case ShaderDataType::Int2:    return 2;
                case ShaderDataType::Int3:    return 3;
                case ShaderDataType::Int4:    return 4;
                case ShaderDataType::Bool:    return 1;
                case ShaderDataType::None:    break;
            }

            return 0;
        }
    };

    class BufferLayout
    {
    public:
        BufferLayout() = default;

        BufferLayout(std::initializer_list<BufferElement> elements)
                : m_Elements(elements)
        {
            CalculateOffsetsAndStride();
        }

        uint32_t GetStride() const { return m_Stride; }
        const std::vector<BufferElement>& GetElements() const { return m_Elements; }

        std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
        std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
        std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
        std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
    private:
        void CalculateOffsetsAndStride()
        {
            size_t offset = 0;
            m_Stride = 0;
            for (auto& element : m_Elements)
            {
                element.Offset = offset;
                offset += element.Size;
                m_Stride += element.Size;
            }
        }
    private:
        std::vector<BufferElement> m_Elements;
        uint32_t m_Stride = 0;
    };

    class VertexBuffer
    {
    public:
        VertexBuffer(uint32_t size);
        VertexBuffer(float* vertices, uint32_t size);
        virtual ~VertexBuffer();

        void Bind() const;
        void Unbind() const;

        void SetData(const void* data, uint32_t size);

        const BufferLayout& GetLayout() const { return m_layout; }
        void SetLayout(const BufferLayout& layout) { m_layout = layout; }

    private:
        GL_ID ID;
        BufferLayout m_layout;
    };

    class IndexBuffer
    {
    public:
        IndexBuffer(uint32_t* indices, uint32_t count);
        ~IndexBuffer();

        void bind() const;
        void unbind() const;

        uint32_t GetCount() const { return m_count; }

    private:
        GL_ID ID;
        uint32_t m_count;
    };

}

#endif //PIXLENGINE_BUFFER_H
