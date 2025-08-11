//
// Created by ChiroYuki on 05/08/2025.
//

#ifndef PIXLENGINE_GEOMETRY_H
#define PIXLENGINE_GEOMETRY_H

#include "Pixl/Core/Base.h"
#include "Pixl/Rendering/Objects/VertexLayout.h"
#include "Pixl/Rendering/Objects/VertexArray.h"

#include <cstdint>

namespace Pixl {

    class Geometry {
    public:
        Geometry() = default;
        virtual ~Geometry() = default;

        void bind() const;
        static void unbind();

        void setVertexData(const void* vertices, uint32_t size, const VertexLayout& layout);
        void setIndexData(const std::vector<uint32_t>& indices);

        const Ref<VertexArray>& getVertexArray() const { return m_vertexArray; }
        uint32_t getVertexCount() const { return m_vertexCount; }
        uint32_t getIndexCount() const { return m_vertexArray ? m_vertexArray->getIndexCount() : 0; }
        bool hasIndices() const { return m_vertexArray && m_vertexArray->hasIndexBuffer(); }

        static Ref<Geometry> createTriangle();
        static Ref<Geometry> createQuad();
        static Ref<Geometry> createCube();

    protected:
        Ref<VertexArray> m_vertexArray;
        uint32_t m_vertexCount = 0;
    };

}

#endif //PIXLENGINE_GEOMETRY_H
