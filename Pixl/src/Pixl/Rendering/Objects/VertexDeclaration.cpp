//
// Created by ChiroYuki on 03/08/2025.
//

#include "Pixl/Rendering/Objects/VertexDeclaration.h"

namespace Pixl {

    std::unordered_map<VertexLayout, VertexDeclaration> VertexDeclaration::s_declarations;

    void VertexDeclaration::Init() {
        s_declarations[VertexLayout::Position] = VertexDeclaration(VertexInputRate::Vertex, {
                {VertexComponent::Position, VertexAttributeType::Float3, 0}
        });

        s_declarations[VertexLayout::PositionColor] = VertexDeclaration(VertexInputRate::Vertex, {
                {VertexComponent::Position, VertexAttributeType::Float3, 0},
                {VertexComponent::Color,    VertexAttributeType::Float4, 0}
        });

        s_declarations[VertexLayout::PositionUV] = VertexDeclaration(VertexInputRate::Vertex, {
                {VertexComponent::Position, VertexAttributeType::Float3, 0},
                {VertexComponent::TexCoord, VertexAttributeType::Float2, 0}
        });

        s_declarations[VertexLayout::PositionNormal] = VertexDeclaration(VertexInputRate::Vertex, {
                {VertexComponent::Position, VertexAttributeType::Float3, 0},
                {VertexComponent::Normal,   VertexAttributeType::Float3, 0}
        });

        s_declarations[VertexLayout::PositionNormalUV] = VertexDeclaration(VertexInputRate::Vertex, {
                {VertexComponent::Position, VertexAttributeType::Float3, 0},
                {VertexComponent::Normal,   VertexAttributeType::Float3, 0},
                {VertexComponent::TexCoord, VertexAttributeType::Float2, 0}
        });

        s_declarations[VertexLayout::PositionNormalColor] = VertexDeclaration(VertexInputRate::Vertex, {
                {VertexComponent::Position, VertexAttributeType::Float3, 0},
                {VertexComponent::Normal,   VertexAttributeType::Float3, 0},
                {VertexComponent::Color,    VertexAttributeType::Float4, 0}
        });

        s_declarations[VertexLayout::PositionNormalUVColor] = VertexDeclaration(VertexInputRate::Vertex, {
                {VertexComponent::Position, VertexAttributeType::Float3, 0},
                {VertexComponent::Normal,   VertexAttributeType::Float3, 0},
                {VertexComponent::TexCoord, VertexAttributeType::Float2, 0},
                {VertexComponent::Color,    VertexAttributeType::Float4, 0}
        });
    }

    const VertexDeclaration& VertexDeclaration::Get(VertexLayout layout) {
        auto it = s_declarations.find(layout);
        if (it != s_declarations.end()) {
            return it->second;
        }

        static VertexDeclaration empty;
        return empty;
    }

}