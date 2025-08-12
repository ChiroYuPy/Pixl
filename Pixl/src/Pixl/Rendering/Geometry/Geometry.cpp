//
// Created by ChiroYuki on 05/08/2025.
//

#include "Pixl/Rendering/Geometry/Geometry.h"

namespace Pixl {

    Geometry::Geometry(VertexFormat format, const void *vertices, size_t vertexDataSize, const unsigned int *indices,
                       size_t indexCount)
            : vertexFormat(std::move(format)), indices(indices != nullptr)
    {
        vao.bind();

        vbo.setData(vertices, vertexDataSize);
        vertexCount = vertexDataSize / vertexFormat.getStride();

        if (indices) {
            ebo.setData(indices, indexCount);
            this->indexCount = indexCount;
        }

        vao.setVertexFormat(vertexFormat);

        vao.unbind();
        vbo.unbind();
        if (indices) ebo.unbind();
    }

    void Geometry::bind() const {
        vao.bind();
    }

    void Geometry::unbind() const {
        vao.unbind();
    }

    size_t Geometry::getIndexCount() const {
        return indexCount;
    }

    size_t Geometry::getVertexCount() const {
        return vertexCount;
    }

    bool Geometry::hasIndices() const {
        return indices;
    }

    Ref<Geometry> GeometryFactory::createCube(const float size) {
        static VertexFormat cubeFormat;

        static bool initialized = false;
        if (!initialized) {
            cubeFormat.addAttribute(VertexAttributeType::Float3, 0, offsetof(Vertex, position));
            cubeFormat.addAttribute(VertexAttributeType::Float4, 1, offsetof(Vertex, color));
            initialized = true;
        }

        const float hSize = size / 2.f;
        Vertex vertices[] = {
                {{-hSize, -hSize, -hSize}, {1.f, 0.f, 0.f, 1.f}},
                {{ hSize, -hSize, -hSize}, {0.f, 1.f, 0.f, 1.f}},
                {{ hSize,  hSize, -hSize}, {0.f, 0.f, 1.f, 1.f}},
                {{-hSize,  hSize, -hSize}, {1.f, 1.f, 0.f, 1.f}},
                {{-hSize, -hSize,  hSize}, {1.f, 0.f, 1.f, 1.f}},
                {{ hSize, -hSize,  hSize}, {0.f, 1.f, 1.f, 1.f}},
                {{ hSize,  hSize,  hSize}, {1.f, 1.f, 1.f, 1.f}},
                {{-hSize,  hSize,  hSize}, {0.f, 0.f, 0.f, 1.f}},
        };

        unsigned int indices[] = {
                0, 1, 2, 2, 3, 0,
                4, 5, 6, 6, 7, 4,
                0, 4, 7, 7, 3, 0,
                1, 5, 6, 6, 2, 1,
                3, 2, 6, 6, 7, 3,
                0, 1, 5, 5, 4, 0,
        };

        return MakeRef<Geometry>(
                cubeFormat,
                vertices, sizeof(vertices),
                indices, sizeof(indices) / sizeof(indices[0])
        );
    }

}