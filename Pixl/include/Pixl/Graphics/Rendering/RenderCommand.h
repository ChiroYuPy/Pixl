//
// Created by ChiroYuki on 01/08/2025.
//

#ifndef PIXLENGINE_RENDERCOMMAND_H
#define PIXLENGINE_RENDERCOMMAND_H

#include <cstdint>
#include <glm/glm.hpp>

#include "Pixl/Graphics/Rendering/Objects/VertexArray.h"

namespace Pixl {

    enum class DrawMode {
        Points          = GL_POINTS,            // Draws each vertex as a single point.
        Lines           = GL_LINES,             // Draws independent lines for every 2 vertices.
        LineStrip       = GL_LINE_STRIP,        // Draws a connected line from vertex to vertex.
        LineLoop        = GL_LINE_LOOP,         // Like LineStrip but connects the last vertex back to the first,
        Triangles       = GL_TRIANGLES,         // Draws separate triangles for every 3 vertices.
        TriangleStrip   = GL_TRIANGLE_STRIP,    // Draws connected triangles sharing vertices.
        TriangleFan     = GL_TRIANGLE_FAN,      // Draws triangles sharing the first vertex,
    };

    enum class ClearBufferMask : uint8_t {
        None    = 0,
        Color   = 1 << 0,
        Depth   = 1 << 1,
        Stencil = 1 << 2,
    };

    enum class CullFaceMode {
        Front,
        Back,
        FrontAndBack
    };

    inline ClearBufferMask operator|(ClearBufferMask a, ClearBufferMask b) {
        return static_cast<ClearBufferMask>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
    }

    inline ClearBufferMask operator&(ClearBufferMask a, ClearBufferMask b) {
        return static_cast<ClearBufferMask>(static_cast<uint8_t>(a) & static_cast<uint8_t>(b));
    }

    class RenderCommand {
    public:
        static void Init();

        static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

        static void SetClearColor(const glm::vec4 &color);

        static void Clear(ClearBufferMask mask = ClearBufferMask::Color | ClearBufferMask::Depth);

        static void DrawIndexed(const Ref<VertexArray>& vertexArray, DrawMode mode, uint32_t indexCount = 0);
        static void DrawArrays(const Ref<VertexArray>& vertexArray, DrawMode mode, uint32_t vertexCount);

        static void EnableDepthTest(bool enabled);
        static void EnableBlend(bool enabled);
        static void EnableCullFace(bool enabled);

        static void SetLineWidth(float width);
        static void SetCullFaceMode(CullFaceMode mode);

        static void CheckErrors(const std::string &location);
    };

}

#endif //PIXLENGINE_RENDERCOMMAND_H
