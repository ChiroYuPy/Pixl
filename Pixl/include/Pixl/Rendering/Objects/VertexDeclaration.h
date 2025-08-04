//
// Created by ChiroYuki on 03/08/2025.
//

#ifndef PIXLENGINE_VERTEXDECLARATION_H
#define PIXLENGINE_VERTEXDECLARATION_H

#include <vector>
#include <unordered_map>
#include "VertexAttributeType.h"

namespace Pixl {

    enum class VertexComponent {
        Position,
        Normal,
        Tangent,
        Color,
        TexCoord,
        BoneIndices,
        BoneWeights,
        Custom
    };

    enum class VertexLayout {
        Position,
        PositionColor,
        PositionUV,
        PositionNormal,
        PositionNormalUV,
        PositionNormalColor,
        PositionNormalUVColor,
    };

    struct VertexInputRate {
        static constexpr int Vertex = 0;
        static constexpr int Instance = 1;
    };

    struct VertexDeclarationComponent {
        VertexComponent component;
        VertexAttributeType type;
        uint32_t componentIndex;

        VertexDeclarationComponent(VertexComponent comp, VertexAttributeType t, uint32_t index = 0)
                : component(comp), type(t), componentIndex(index) {}
    };

    class VertexDeclaration {
    public:
        VertexDeclaration() = default;
        VertexDeclaration(int inputRate, std::initializer_list<VertexDeclarationComponent> components)
                : m_inputRate(inputRate), m_components(components) {}

        static void Init();
        static const VertexDeclaration& Get(VertexLayout layout);

        int GetInputRate() const { return m_inputRate; }
        const std::vector<VertexDeclarationComponent>& GetComponents() const { return m_components; }

    private:
        int m_inputRate = VertexInputRate::Vertex;
        std::vector<VertexDeclarationComponent> m_components;

        static std::unordered_map<VertexLayout, VertexDeclaration> s_declarations;
    };

}

#endif //PIXLENGINE_VERTEXDECLARATION_H
