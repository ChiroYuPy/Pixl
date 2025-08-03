//
// Created by ChiroYuki on 02/08/2025.
//

#ifndef PIXLENGINE_CUBEGEOMETRY_H
#define PIXLENGINE_CUBEGEOMETRY_H

#include <cstdint>
#include "Pixl/Rendering/Objects/VertexArray.h"
#include "IGeometry.h"

namespace Pixl {

    class CubeGeometry : public IGeometry {
    private:
        VertexArray m_VAO;
        Ref<VertexBuffer> m_VBO;
        Ref<IndexBuffer> m_EBO;
        uint32_t m_indexCount = 0;

        static constexpr float s_Vertices[8 * 3] = {
                -0.5f, -0.5f, -0.5f,  // 0
                0.5f, -0.5f, -0.5f,  // 1
                0.5f,  0.5f, -0.5f,  // 2
                -0.5f,  0.5f, -0.5f,  // 3
                -0.5f, -0.5f,  0.5f,  // 4
                0.5f, -0.5f,  0.5f,  // 5
                0.5f,  0.5f,  0.5f,  // 6
                -0.5f,  0.5f,  0.5f   // 7
        };

        static constexpr uint32_t s_Indices[36] = {
                0, 1, 2, 2, 3, 0,     // back
                4, 5, 6, 6, 7, 4,     // front
                4, 5, 1, 1, 0, 4,     // bottom
                7, 6, 2, 2, 3, 7,     // top
                4, 0, 3, 3, 7, 4,     // left
                5, 1, 2, 2, 6, 5      // right
        };

    public:
        CubeGeometry();

        void bind() const override;

        void unbind() const override;

        uint32_t getIndexCount() const override;
    };

    constexpr float CubeGeometry::s_Vertices[];
    constexpr uint32_t CubeGeometry::s_Indices[];

}

#endif //PIXLENGINE_CUBEGEOMETRY_H
