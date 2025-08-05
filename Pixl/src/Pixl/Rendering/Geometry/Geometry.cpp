//
// Created by ChiroYuki on 05/08/2025.
//

#include "Pixl/Rendering/Geometry/Geometry.h"

namespace Pixl {

    void Geometry::setVertexData(const void* vertices, uint32_t size, const VertexLayout& layout) {
        if (!m_vertexArray) {
            m_vertexArray = MakeRef<VertexArray>();
        }

        auto vertexBuffer = MakeRef<VertexBuffer>(vertices, size);
        m_vertexArray->addVertexBuffer(vertexBuffer, layout);
        m_vertexCount = size / layout.getStride();
    }

    void Geometry::setIndexData(const std::vector<uint32_t>& indices) {
        if (!m_vertexArray) {
            m_vertexArray = MakeRef<VertexArray>();
        }

        auto indexBuffer = MakeRef<IndexBuffer>(indices.data(), indices.size());
        m_vertexArray->setIndexBuffer(indexBuffer);
    }

    Ref<Geometry> Geometry::createTriangle() {
        auto geometry = MakeRef<Geometry>();

        float vertices[] = {
                -0.5f, -0.5f, 0.0f,  // Position
                0.5f, -0.5f, 0.0f,
                0.0f,  0.5f, 0.0f
        };

        VertexLayout layout(VertexComponentLayoutTemplate::Position);
        geometry->setVertexData(vertices, sizeof(vertices), layout);

        return geometry;
    }

    Ref<Geometry> Geometry::createQuad() {
        auto geometry = MakeRef<Geometry>();

        float vertices[] = {
                -0.5f, -0.5f, 0.0f,  0.0f, 0.0f,  // Position, TexCoord
                0.5f, -0.5f, 0.0f,  1.0f, 0.0f,
                0.5f,  0.5f, 0.0f,  1.0f, 1.0f,
                -0.5f,  0.5f, 0.0f,  0.0f, 1.0f
        };

        std::vector<uint32_t> indices = {0, 1, 2, 2, 3, 0};

        VertexLayout layout(VertexComponentLayoutTemplate::PositionUV);
        geometry->setVertexData(vertices, sizeof(vertices), layout);
        geometry->setIndexData(indices);

        return geometry;
    }

    Ref<Geometry> Geometry::createCube() {
        auto geometry = MakeRef<Geometry>();

        // Positions des 24 sommets du cube (6 faces × 4 sommets)
        float vertices[] = {
                -0.5f, -0.5f,  0.5f,  // 0
                0.5f, -0.5f,  0.5f,  // 1
                0.5f,  0.5f,  0.5f,  // 2
                -0.5f,  0.5f,  0.5f,  // 3

                -0.5f, -0.5f, -0.5f,  // 4
                0.5f, -0.5f, -0.5f,  // 5
                0.5f,  0.5f, -0.5f,  // 6
                -0.5f,  0.5f, -0.5f,  // 7

                -0.5f, -0.5f, -0.5f,  // 8
                -0.5f, -0.5f,  0.5f,  // 9
                -0.5f,  0.5f,  0.5f,  // 10
                -0.5f,  0.5f, -0.5f,  // 11

                0.5f, -0.5f, -0.5f,  // 12
                0.5f, -0.5f,  0.5f,  // 13
                0.5f,  0.5f,  0.5f,  // 14
                0.5f,  0.5f, -0.5f,  // 15

                -0.5f,  0.5f,  0.5f,  // 16
                0.5f,  0.5f,  0.5f,  // 17
                0.5f,  0.5f, -0.5f,  // 18
                -0.5f,  0.5f, -0.5f,  // 19

                -0.5f, -0.5f,  0.5f,  // 20
                0.5f, -0.5f,  0.5f,  // 21
                0.5f, -0.5f, -0.5f,  // 22
                -0.5f, -0.5f, -0.5f   // 23
        };

        std::vector<uint32_t> indices = {
                0, 1, 2, 2, 3, 0,
                4, 6, 5, 6, 4, 7,
                8, 9,10,10,11, 8,
                12,14,13,14,12,15,
                16,17,18,18,19,16,
                20,22,21,22,20,23
        };

        VertexLayout layout(VertexComponentLayoutTemplate::Position);
        geometry->setVertexData(vertices, sizeof(vertices), layout);
        geometry->setIndexData(indices);

        return geometry;
    }

}