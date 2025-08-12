//
// Created by ChiroYuki on 01/08/2025.
//

#ifndef PIXLENGINE_BUFFER_H
#define PIXLENGINE_BUFFER_H

#include "Pixl/Core/Base.h"

#include <glad/glad.h>

namespace Pixl {

    class Buffer {
    protected:
        GLuint ID;
        GLenum target;

    public:
        Buffer(GLenum targetType) : target(targetType) {
            glGenBuffers(1, &ID);
            if (ID == 0)
                throw std::runtime_error("Failed to generate buffer");
        }

        virtual ~Buffer() {
            if (ID != 0)
                glDeleteBuffers(1, &ID);
        }

        void bind() const {
            glBindBuffer(target, ID);
        }

        void unbind() const {
            glBindBuffer(target, 0);
        }

        virtual void setData(const void* data, size_t size, GLenum usage = GL_STATIC_DRAW) {
            bind();
            glBufferData(target, size, data, usage);
        }

        GLuint getID() const { return ID; }
    };

    class VertexBuffer : public Buffer {
    public:
        VertexBuffer() : Buffer(GL_ARRAY_BUFFER) {}
    };

    class IndexBuffer : public Buffer {
        size_t count;
    public:
        IndexBuffer() : Buffer(GL_ELEMENT_ARRAY_BUFFER), count(0) {}

        void setData(const void* data, size_t countIndices, GLenum usage = GL_STATIC_DRAW) override {
            count = countIndices;
            Buffer::setData(data, count * sizeof(unsigned int), usage);
        }

        size_t getCount() const { return count; }
    };

}

#endif //PIXLENGINE_BUFFER_H
