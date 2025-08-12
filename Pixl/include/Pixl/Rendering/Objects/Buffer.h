//
// Created by ChiroYuki on 01/08/2025.
//

#ifndef PIXLENGINE_BUFFER_H
#define PIXLENGINE_BUFFER_H

#include "Pixl/Core/Base.h"

#include <glad/glad.h>

namespace Pixl {

    class VertexBuffer {
    public:
        GLuint ID;

        VertexBuffer() {
            glGenBuffers(1, &ID);
            if (ID == 0)
                throw std::runtime_error("Failed to generate VBO");
        }

        ~VertexBuffer() {
            if (ID != 0)
                glDeleteBuffers(1, &ID);
        }

        void bind() const {
            glBindBuffer(GL_ARRAY_BUFFER, ID);
        }

        void unbind() const {
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        void setData(const void* data, size_t size, GLenum usage = GL_STATIC_DRAW) {
            bind();
            glBufferData(GL_ARRAY_BUFFER, size, data, usage);
        }
    };

    class IndexBuffer {
    public:
        GLuint ID;
        size_t count;

        IndexBuffer() : count(0) {
            glGenBuffers(1, &ID);
            if (ID == 0)
                throw std::runtime_error("Failed to generate EBO");
        }

        ~IndexBuffer() {
            if (ID != 0)
                glDeleteBuffers(1, &ID);
        }

        void bind() const {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
        }

        void unbind() const {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }

        void setData(const void* data, size_t countIndices, GLenum usage = GL_STATIC_DRAW) {
            bind();
            count = countIndices;
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, usage);
        }
    };


}

#endif //PIXLENGINE_BUFFER_H
