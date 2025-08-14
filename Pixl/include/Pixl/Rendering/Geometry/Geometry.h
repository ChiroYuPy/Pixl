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
                 const unsigned int* indices = nullptr, size_t indexCount = 0);

        void bind() const;

        void unbind() const;

        size_t getIndexCount() const;

        size_t getVertexCount() const;

        bool hasIndices() const;

    protected:
        VertexArray vao;
        VertexBuffer vbo;
        IndexBuffer ebo;

        VertexFormat vertexFormat;
        size_t indexCount = 0;
        size_t vertexCount = 0;
        bool indices = false;
    };

    struct Vertex {
        float position[3];
        static VertexFormat* format;
    };

    class GeometryFactory {
    public:
        static Ref<Geometry> createCube(float size = 1.f);
        static Ref<Geometry> createSphere();
        static Ref<Geometry> createPlane();
    };

}

#endif //PIXLENGINE_GEOMETRY_H
