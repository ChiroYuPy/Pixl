//
// Created by ChiroYuki on 02/08/2025.
//

#include "Pixl/Rendering/Geometry/CubeGeometry.h"

namespace Pixl {

    CubeGeometry::CubeGeometry()
    {
        m_indexCount = static_cast<uint32_t>(sizeof(s_Indices) / sizeof(uint32_t));

        m_VBO = MakeRef<VertexBuffer>(
                const_cast<float*>(s_Vertices),
                static_cast<uint32_t>(sizeof(s_Vertices))
        );

        m_EBO = MakeRef<IndexBuffer>(
                const_cast<uint32_t*>(s_Indices),
                m_indexCount
        );

        BufferLayout layout = {
                { ShaderDataType::Float3, "a_Position" }
        };
        m_VBO->SetLayout(layout);

        // Configuration du VAO
        m_VAO.bind();
        m_VAO.AddVertexBuffer(m_VBO);
        m_VAO.SetIndexBuffer(m_EBO);
        m_VAO.unbind();
    }

    void CubeGeometry::bind() const {
        m_VAO.bind();
    }

    void CubeGeometry::unbind() const {
        m_VAO.unbind();
    }

    uint32_t CubeGeometry::getIndexCount() const {
        return m_indexCount;
    }

}