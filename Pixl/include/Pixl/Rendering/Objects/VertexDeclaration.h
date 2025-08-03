//
// Created by ChiroYuki on 03/08/2025.
//

#ifndef PIXLENGINE_VERTEXDECLARATION_H
#define PIXLENGINE_VERTEXDECLARATION_H

#include <vector>
#include <unordered_map>
#include "ShaderData.h"

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
        ComponentType type;
        uint32_t componentIndex;

        VertexDeclarationComponent(VertexComponent comp, ComponentType t, uint32_t index = 0)
                : component(comp), type(t), componentIndex(index) {}
    };

    class VertexDeclaration {
    public:
        VertexDeclaration() = default;
        VertexDeclaration(int inputRate, std::initializer_list<VertexDeclarationComponent> components)
                : m_inputRate(inputRate), m_components(components) {}

        static void Initialize();
        static const VertexDeclaration& Get(VertexLayout layout);

        int GetInputRate() const { return m_inputRate; }
        const std::vector<VertexDeclarationComponent>& GetComponents() const { return m_components; }

    private:
        int m_inputRate = VertexInputRate::Vertex;
        std::vector<VertexDeclarationComponent> m_components;

        static std::unordered_map<VertexLayout, VertexDeclaration> s_declarations;
    };

    class LayoutValidator {
    public:
        // Vérifie si un layout de géométrie est compatible avec les exigences d'un matériau
        static bool IsCompatible(VertexLayout geometryLayout, VertexLayout materialRequiredLayout) {
            // Un layout plus riche peut satisfaire un layout plus simple
            return HasRequiredComponents(geometryLayout, materialRequiredLayout);
        }

        // Vérifie si le layout de géométrie contient tous les composants requis
        static bool HasRequiredComponents(VertexLayout geometryLayout, VertexLayout requiredLayout) {
            const auto& geometryDecl = VertexDeclaration::Get(geometryLayout);
            const auto& requiredDecl = VertexDeclaration::Get(requiredLayout);

            const auto& geometryComponents = geometryDecl.GetComponents();
            const auto& requiredComponents = requiredDecl.GetComponents();

            // Vérifier que chaque composant requis est présent dans la géométrie
            for (const auto& required : requiredComponents) {
                bool found = false;
                for (const auto& geometry : geometryComponents) {
                    if (geometry.component == required.component &&
                        geometry.type == required.type) {
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    return false;
                }
            }
            return true;
        }

        // Suggestions de layouts compatibles
        static std::vector<VertexLayout> GetCompatibleLayouts(VertexLayout requiredLayout) {
            std::vector<VertexLayout> compatible;

            // Tous les layouts possibles
            std::vector<VertexLayout> allLayouts = {
                    VertexLayout::Position,
                    VertexLayout::PositionColor,
                    VertexLayout::PositionUV,
                    VertexLayout::PositionNormal,
                    VertexLayout::PositionNormalUV,
                    VertexLayout::PositionNormalColor,
                    VertexLayout::PositionNormalUVColor
            };

            for (auto layout : allLayouts) {
                if (IsCompatible(layout, requiredLayout)) {
                    compatible.push_back(layout);
                }
            }

            return compatible;
        }
    };
}

#endif //PIXLENGINE_VERTEXDECLARATION_H
