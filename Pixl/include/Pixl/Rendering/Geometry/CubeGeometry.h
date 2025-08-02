//
// Created by ChiroYuki on 02/08/2025.
//

#ifndef PIXLENGINE_CUBEGEOMETRY_H
#define PIXLENGINE_CUBEGEOMETRY_H

#include <cstdint>
#include "Pixl/Rendering/Objects/VertexArray.h"
#include "Geometry.h"

namespace Pixl {

    class CubeGeometry : public Geometry {
    private:
        VertexArray m_VAO;
        VertexBuffer m_VBO;
        IndexBuffer m_EBO;
        uint32_t m_indexCount = 0;

        // Données statiques : sommets (positions uniquement)
        static constexpr float s_Vertices[] = {
                -0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f,
                0.5f,  0.5f, -0.5f, -0.5f,  0.5f, -0.5f,
                -0.5f, -0.5f,  0.5f,  0.5f, -0.5f,  0.5f,
                0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f
        };

        // Données statiques : indices pour triangles
        static constexpr uint32_t s_Indices[] = {
                0, 1, 2, 2, 3, 0,     // back
                4, 5, 6, 6, 7, 4,     // front
                4, 5, 1, 1, 0, 4,     // bottom
                7, 6, 2, 2, 3, 7,     // top
                4, 0, 3, 3, 7, 4,     // left
                5, 1, 2, 2, 6, 5      // right
        };

    public:
        CubeGeometry()
                : m_VBO(nullptr, 0), m_EBO(nullptr, 0)
        {
            // Taille des données
            m_indexCount = static_cast<uint32_t>(sizeof(s_Indices) / sizeof(uint32_t));

            // Création des buffers
            m_VBO = VertexBuffer(
                    const_cast<float*>(s_Vertices),
                    static_cast<uint32_t>(sizeof(s_Vertices))
            );

            m_EBO = IndexBuffer(
                    const_cast<uint32_t*>(s_Indices),
                    m_indexCount
            );

            // Définition du layout des attributs
            BufferLayout layout = {
                    { ShaderDataType::Float3, "a_Position" }
            };
            m_VBO.SetLayout(layout);

            // Configuration du VAO
            m_VAO.bind();
            m_VAO.AddVertexBuffer(std::make_shared<VertexBuffer>(m_VBO));
            m_VAO.SetIndexBuffer(std::make_shared<IndexBuffer>(m_EBO));
            m_VAO.unbind();
        }

        void bind() const override {
            m_VAO.bind();
        }

        void unbind() const override {
            m_VAO.unbind();
        }

        uint32_t getIndexCount() const override {
            return m_indexCount;
        }
    };

    // Définition des tableaux statiques (nécessaire pour les constexpr dans headers avec MSVC/gcc)
    constexpr float CubeGeometry::s_Vertices[];
    constexpr uint32_t CubeGeometry::s_Indices[];

}

#endif //PIXLENGINE_CUBEGEOMETRY_H
