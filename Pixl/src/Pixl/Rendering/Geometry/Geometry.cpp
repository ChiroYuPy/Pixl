//
// Created by ChiroYuki on 05/08/2025.
//

#include "Pixl/Rendering/Geometry/Geometry.h"

#include <cmath>

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
            initialized = true;
        }

        const float hSize = size / 2.f;
        Vertex vertices[] = {
                {{-hSize, -hSize, -hSize}},
                {{ hSize, -hSize, -hSize}},
                {{ hSize,  hSize, -hSize}},
                {{-hSize,  hSize, -hSize}},
                {{-hSize, -hSize,  hSize}},
                {{ hSize, -hSize,  hSize}},
                {{ hSize,  hSize,  hSize}},
                {{-hSize,  hSize,  hSize}},
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

    Ref<Geometry> GeometryFactory::createPlane() {
        static VertexFormat planeFormat;

        static bool initialized = false;
        if (!initialized) {
            planeFormat.addAttribute(VertexAttributeType::Float3, 0, offsetof(Vertex, position));
            initialized = true;
        }

        Vertex vertices[] = {
                {{-0.5f, 0.0f, -0.5f}},
                {{ 0.5f, 0.0f, -0.5f}},
                {{ 0.5f, 0.0f,  0.5f}},
                {{-0.5f, 0.0f,  0.5f}},
        };

        unsigned int indices[] = {
                0, 1, 2,
                2, 3, 0
        };

        return MakeRef<Geometry>(
                planeFormat,
                vertices, sizeof(vertices),
                indices, sizeof(indices) / sizeof(indices[0])
        );
    }

    Ref<Geometry> GeometryFactory::createSphere() {
        static VertexFormat sphereFormat;

        static bool initialized = false;
        if (!initialized) {
            sphereFormat.addAttribute(VertexAttributeType::Float3, 0, offsetof(Vertex, position));
            initialized = true;
        }

        const unsigned int latitudeSegments = 16;
        const unsigned int longitudeSegments = 16;
        const float radius = 0.5f;

        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;

        for (unsigned int y = 0; y <= latitudeSegments; y++) {
            for (unsigned int x = 0; x <= longitudeSegments; x++) {
                float xSegment = (float)x / (float)longitudeSegments;
                float ySegment = (float)y / (float)latitudeSegments;
                float xPos = radius * std::cos(xSegment * 2.0f * M_PI) * std::sin(ySegment * M_PI);
                float yPos = radius * std::cos(ySegment * M_PI);
                float zPos = radius * std::sin(xSegment * 2.0f * M_PI) * std::sin(ySegment * M_PI);

                vertices.push_back({{xPos, yPos, zPos}});
            }
        }

        for (unsigned int y = 0; y < latitudeSegments; y++) {
            for (unsigned int x = 0; x < longitudeSegments; x++) {
                unsigned int i0 = y       * (longitudeSegments + 1) + x;
                unsigned int i1 = (y + 1) * (longitudeSegments + 1) + x;
                unsigned int i2 = (y + 1) * (longitudeSegments + 1) + x + 1;
                unsigned int i3 = y       * (longitudeSegments + 1) + x + 1;

                indices.push_back(i0);
                indices.push_back(i1);
                indices.push_back(i2);

                indices.push_back(i2);
                indices.push_back(i3);
                indices.push_back(i0);
            }
        }

        return MakeRef<Geometry>(
                sphereFormat,
                vertices.data(), vertices.size() * sizeof(Vertex),
                indices.data(), indices.size()
        );
    }

}