//
// Created by ChiroYuki on 05/08/2025.
//

#ifndef PIXLENGINE_GEOMETRY_H
#define PIXLENGINE_GEOMETRY_H

#include "Pixl/Core/Base.h"
#include "Pixl/Rendering/Objects/VertexFormat.h"
#include "Pixl/Rendering/Objects/VertexArray.h"

#include <cstdint>
#include <utility>

namespace Pixl {

    class Geometry {
    public:
        Geometry(VertexFormat format, const void* vertices, size_t vertexDataSize,
                 const unsigned int* indices = nullptr, size_t indexCount = 0)
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

        void bind() const {
            vao.bind();
        }

        void unbind() const {
            vao.unbind();
        }

        size_t getIndexCount() const {
            return indexCount;
        }

        size_t getVertexCount() const {
            return vertexCount;
        }

        bool hasIndices() const {
            return indices;
        }

        struct Vertex {
            float position[3];
            float color[4];
            static VertexFormat* format;
        };

        static Ref<Geometry> createCube() {
            static VertexFormat cubeFormat;

            static bool initialized = false;
            if (!initialized) {
                cubeFormat.addAttribute(VertexAttributeType::Float3, 0, offsetof(Vertex, position));
                cubeFormat.addAttribute(VertexAttributeType::Float4, 1, offsetof(Vertex, color));
                initialized = true;
            }

            Vertex vertices[] = {
                    {{-1.f, -1.f, -1.f}, {1.f, 0.f, 0.f, 1.f}},
                    {{ 1.f, -1.f, -1.f}, {0.f, 1.f, 0.f, 1.f}},
                    {{ 1.f,  1.f, -1.f}, {0.f, 0.f, 1.f, 1.f}},
                    {{-1.f,  1.f, -1.f}, {1.f, 1.f, 0.f, 1.f}},
                    {{-1.f, -1.f,  1.f}, {1.f, 0.f, 1.f, 1.f}},
                    {{ 1.f, -1.f,  1.f}, {0.f, 1.f, 1.f, 1.f}},
                    {{ 1.f,  1.f,  1.f}, {1.f, 1.f, 1.f, 1.f}},
                    {{-1.f,  1.f,  1.f}, {0.f, 0.f, 0.f, 1.f}},
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

    protected:
        VertexArray vao;
        VertexBuffer vbo;
        IndexBuffer ebo;

        VertexFormat vertexFormat;
        size_t indexCount = 0;
        size_t vertexCount = 0;
        bool indices = false;
    };

}

#endif //PIXLENGINE_GEOMETRY_H
