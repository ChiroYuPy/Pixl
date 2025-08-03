//
// Created by ChiroYuki on 01/08/2025.
//

#ifndef PIXLENGINE_BUFFER_H
#define PIXLENGINE_BUFFER_H

#include "glad/glad.h"
#include "Pixl/Core/Base.h"

#include <utility>
#include <vector>
#include <string>
#include <unordered_map>

namespace Pixl {

    class VertexBuffer {
    public:
        VertexBuffer(uint32_t size);
        VertexBuffer(float* vertices, uint32_t size);
        virtual ~VertexBuffer();

        void bind() const;
        void unbind() const;

        void setData(const void* data, uint32_t size);

    private:
        GL_ID ID;
    };

    class IndexBuffer {
    public:
        IndexBuffer(uint32_t* indices, uint32_t count);
        ~IndexBuffer();

        void bind() const;
        void unbind() const;

        uint32_t GetCount() const { return m_count; }

    private:
        GL_ID ID;
        uint32_t m_count;
    };

}

#endif //PIXLENGINE_BUFFER_H
