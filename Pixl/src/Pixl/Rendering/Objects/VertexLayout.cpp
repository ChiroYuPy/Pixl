//
// Created by ChiroYuki on 05/08/2025.
//

#include "Pixl/Rendering/Objects/VertexLayout.h"

#include <glad/glad.h>

namespace Pixl {

    VertexAttribute::VertexAttribute(std::string name, VertexAttributeType type, VertexComponent component,
                                     bool normalized)
            : name(std::move(name)), type(type), component(component), offset(0), normalized(normalized) {}

    VertexAttribute::VertexAttribute(VertexComponent component, VertexAttributeType type, bool normalized)
            : type(type), component(component), offset(0), normalized(normalized) {
        name = getComponentShaderName(component);
    }

    std::string VertexAttribute::getComponentShaderName(VertexComponent component) {
        switch (component) {
            case VertexComponent::Position: return "a_Position";
            case VertexComponent::Normal: return "a_Normal";
            case VertexComponent::Tangent: return "a_Tangent";
            case VertexComponent::Color: return "a_Color";
            case VertexComponent::TexCoord: return "a_TexCoord";
            case VertexComponent::TexCoord2: return "a_TexCoord2";
            case VertexComponent::BoneIndices: return "a_BoneIndices";
            case VertexComponent::BoneWeights: return "a_BoneWeights";
            case VertexComponent::Custom: return "a_Custom";
        }
        return "a_Custom";
    }

    VertexLayout::VertexLayout(VertexComponentLayoutTemplate layoutTemplate) : m_stride(0) {
        createFromTemplate(layoutTemplate);
    }

    void VertexLayout::addAttribute(const VertexAttribute &attribute) {
        m_attributes.push_back(attribute);
        m_attributes.back().offset = m_stride;
        m_stride += getAttributeSize(attribute.type);
    }

    void VertexLayout::addComponent(VertexComponent component) {
        VertexAttributeType type = getDefaultTypeForComponent(component);
        addAttribute(VertexAttribute(component, type));
    }

    const std::vector<VertexAttribute> &VertexLayout::getAttributes() const { return m_attributes; }

    uint32_t VertexLayout::getStride() const { return m_stride; }

    bool VertexLayout::hasComponent(VertexComponent component) const {
        for (const auto& attr : m_attributes) {
            if (attr.component == component) return true;
        }
        return false;
    }

    uint32_t VertexLayout::getComponentOffset(VertexComponent component) const {
        for (const auto& attr : m_attributes) {
            if (attr.component == component) return attr.offset;
        }
        return 0;
    }

    uint32_t VertexLayout::getAttributeSize(VertexAttributeType type) {
        switch (type) {
            case VertexAttributeType::Float: return sizeof(float);
            case VertexAttributeType::Float2: return 2 * sizeof(float);
            case VertexAttributeType::Float3: return 3 * sizeof(float);
            case VertexAttributeType::Float4: return 4 * sizeof(float);
            case VertexAttributeType::Int: return sizeof(int);
            case VertexAttributeType::Int2: return 2 * sizeof(int);
            case VertexAttributeType::Int3: return 3 * sizeof(int);
            case VertexAttributeType::Int4: return 4 * sizeof(int);
        }
        return 0;
    }

    uint32_t VertexLayout::getAttributeComponentCount(VertexAttributeType type) {
        switch (type) {
            case VertexAttributeType::Float:
            case VertexAttributeType::Int: return 1;
            case VertexAttributeType::Float2:
            case VertexAttributeType::Int2: return 2;
            case VertexAttributeType::Float3:
            case VertexAttributeType::Int3: return 3;
            case VertexAttributeType::Float4:
            case VertexAttributeType::Int4: return 4;
        }
        return 0;
    }

    uint32_t VertexLayout::getAttributeGLType(VertexAttributeType type) {
        switch (type) {
            case VertexAttributeType::Float:
            case VertexAttributeType::Float2:
            case VertexAttributeType::Float3:
            case VertexAttributeType::Float4: return GL_FLOAT;
            case VertexAttributeType::Int:
            case VertexAttributeType::Int2:
            case VertexAttributeType::Int3:
            case VertexAttributeType::Int4: return GL_INT;
        }
        return GL_FLOAT;
    }

    void VertexLayout::createFromTemplate(VertexComponentLayoutTemplate layoutTemplate) {
        switch (layoutTemplate) {
            case VertexComponentLayoutTemplate::Position:
                addComponent(VertexComponent::Position);
                break;
            case VertexComponentLayoutTemplate::PositionColor:
                addComponent(VertexComponent::Position);
                addComponent(VertexComponent::Color);
                break;
            case VertexComponentLayoutTemplate::PositionUV:
                addComponent(VertexComponent::Position);
                addComponent(VertexComponent::TexCoord);
                break;
            case VertexComponentLayoutTemplate::PositionNormal:
                addComponent(VertexComponent::Position);
                addComponent(VertexComponent::Normal);
                break;
            case VertexComponentLayoutTemplate::PositionNormalUV:
                addComponent(VertexComponent::Position);
                addComponent(VertexComponent::Normal);
                addComponent(VertexComponent::TexCoord);
                break;
            case VertexComponentLayoutTemplate::PositionNormalColor:
                addComponent(VertexComponent::Position);
                addComponent(VertexComponent::Normal);
                addComponent(VertexComponent::Color);
                break;
            case VertexComponentLayoutTemplate::PositionNormalUVColor:
                addComponent(VertexComponent::Position);
                addComponent(VertexComponent::Normal);
                addComponent(VertexComponent::TexCoord);
                addComponent(VertexComponent::Color);
                break;
            case VertexComponentLayoutTemplate::PositionNormalTangentUV:
                addComponent(VertexComponent::Position);
                addComponent(VertexComponent::Normal);
                addComponent(VertexComponent::Tangent);
                addComponent(VertexComponent::TexCoord);
                break;
            case VertexComponentLayoutTemplate::SkinnedMesh:
                addComponent(VertexComponent::Position);
                addComponent(VertexComponent::Normal);
                addComponent(VertexComponent::TexCoord);
                addComponent(VertexComponent::BoneIndices);
                addComponent(VertexComponent::BoneWeights);
                break;
        }
    }

    VertexAttributeType VertexLayout::getDefaultTypeForComponent(VertexComponent component) {
        switch (component) {
            case VertexComponent::Position: return VertexAttributeType::Float3;
            case VertexComponent::Normal: return VertexAttributeType::Float3;
            case VertexComponent::Tangent: return VertexAttributeType::Float4;
            case VertexComponent::Color: return VertexAttributeType::Float4;
            case VertexComponent::TexCoord: return VertexAttributeType::Float2;
            case VertexComponent::TexCoord2: return VertexAttributeType::Float2;
            case VertexComponent::BoneIndices: return VertexAttributeType::Int4;
            case VertexComponent::BoneWeights: return VertexAttributeType::Float4;
            case VertexComponent::Custom: return VertexAttributeType::Float;
        }
        return VertexAttributeType::Float;
    }
}