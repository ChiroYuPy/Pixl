//
// Created by ChiroYuki on 05/08/2025.
//

#ifndef PIXLENGINE_VERTEXLAYOUT_H
#define PIXLENGINE_VERTEXLAYOUT_H

#include <string>
#include <cstdint>
#include <utility>
#include <vector>

namespace Pixl {

    enum class VertexAttributeType {
        Float,
        Float2,
        Float3,
        Float4,
        Int,
        Int2,
        Int3,
        Int4
    };

    enum class VertexComponent {
        Position,
        Normal,
        Tangent,
        Color,
        TexCoord,
        TexCoord2,
        BoneIndices,
        BoneWeights,
        Custom
    };

    enum class VertexComponentLayoutTemplate {
        Position,
        PositionColor,
        PositionUV,
        PositionNormal,
        PositionNormalUV,
        PositionNormalColor,
        PositionNormalUVColor,
        PositionNormalTangentUV,
        SkinnedMesh
    };

    struct VertexAttribute {
        std::string name;
        VertexAttributeType type;
        VertexComponent component;
        uint32_t offset;
        bool normalized;

        VertexAttribute(std::string name, VertexAttributeType type, VertexComponent component = VertexComponent::Custom, bool normalized = false);

        VertexAttribute(VertexComponent component, VertexAttributeType type, bool normalized = false);

        static std::string getComponentShaderName(VertexComponent component);
    };

    class VertexLayout {
    public:
        VertexLayout() : m_stride(0) {}

        explicit VertexLayout(VertexComponentLayoutTemplate layoutTemplate);

        void addAttribute(const VertexAttribute& attribute);

        void addComponent(VertexComponent component);

        const std::vector<VertexAttribute>& getAttributes() const;
        uint32_t getStride() const;

        bool hasComponent(VertexComponent component) const;

        uint32_t getComponentOffset(VertexComponent component) const;

        static uint32_t getAttributeSize(VertexAttributeType type);

        static uint32_t getAttributeComponentCount(VertexAttributeType type);

        static uint32_t getAttributeGLType(VertexAttributeType type);

    private:
        void createFromTemplate(VertexComponentLayoutTemplate layoutTemplate);

        static VertexAttributeType getDefaultTypeForComponent(VertexComponent component);

        std::vector<VertexAttribute> m_attributes;
        uint32_t m_stride;
    };

}

#endif //PIXLENGINE_VERTEXLAYOUT_H
