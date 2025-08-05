//
// Created by ChiroYuki on 01/08/2025.
//

#ifndef PIXLENGINE_RENDERCOMMAND_H
#define PIXLENGINE_RENDERCOMMAND_H

#include <cstdint>
#include <string>
#include <glm/glm.hpp>

#include "Pixl/Rendering/Objects/VertexArray.h"

namespace Pixl {

    enum class DrawMode {
        Points          = GL_POINTS,            // Draws each vertex as a single point.
        Lines           = GL_LINES,             // Draws independent lines for every 2 vertices.
        LineStrip       = GL_LINE_STRIP,        // Draws a connected line from vertex to vertex.
        LineLoop        = GL_LINE_LOOP,         // Like LineStrip but connects the last vertex back to the first.
        Triangles       = GL_TRIANGLES,         // Draws separate triangles for every 3 vertices.
        TriangleStrip   = GL_TRIANGLE_STRIP,    // Draws connected triangles sharing vertices.
        TriangleFan     = GL_TRIANGLE_FAN,      // Draws triangles sharing the first vertex.
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

    // Operators for ClearBufferMask bitwise operations
    inline ClearBufferMask operator|(ClearBufferMask a, ClearBufferMask b) {
        return static_cast<ClearBufferMask>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
    }

    inline ClearBufferMask operator&(ClearBufferMask a, ClearBufferMask b) {
        return static_cast<ClearBufferMask>(static_cast<uint8_t>(a) & static_cast<uint8_t>(b));
    }

    inline ClearBufferMask operator^(ClearBufferMask a, ClearBufferMask b) {
        return static_cast<ClearBufferMask>(static_cast<uint8_t>(a) ^ static_cast<uint8_t>(b));
    }

    inline ClearBufferMask operator~(ClearBufferMask a) {
        return static_cast<ClearBufferMask>(~static_cast<uint8_t>(a));
    }

    inline ClearBufferMask& operator|=(ClearBufferMask& a, ClearBufferMask b) {
        a = a | b;
        return a;
    }

    inline ClearBufferMask& operator&=(ClearBufferMask& a, ClearBufferMask b) {
        a = a & b;
        return a;
    }

    enum class BlendFunction {
        Zero                = GL_ZERO,
        One                 = GL_ONE,
        SrcColor            = GL_SRC_COLOR,
        OneMinusSrcColor    = GL_ONE_MINUS_SRC_COLOR,
        DstColor            = GL_DST_COLOR,
        OneMinusDstColor    = GL_ONE_MINUS_DST_COLOR,
        SrcAlpha            = GL_SRC_ALPHA,
        OneMinusSrcAlpha    = GL_ONE_MINUS_SRC_ALPHA,
        DstAlpha            = GL_DST_ALPHA,
        OneMinusDstAlpha    = GL_ONE_MINUS_DST_ALPHA,
        ConstantColor       = GL_CONSTANT_COLOR,
        OneMinusConstantColor = GL_ONE_MINUS_CONSTANT_COLOR,
        ConstantAlpha       = GL_CONSTANT_ALPHA,
        OneMinusConstantAlpha = GL_ONE_MINUS_CONSTANT_ALPHA
    };

    enum class BlendEquation {
        Add             = GL_FUNC_ADD,
        Subtract        = GL_FUNC_SUBTRACT,
        ReverseSubtract = GL_FUNC_REVERSE_SUBTRACT,
        Min             = GL_MIN,
        Max             = GL_MAX
    };

    enum class DepthFunction {
        Never           = GL_NEVER,
        Less            = GL_LESS,
        Equal           = GL_EQUAL,
        LessEqual       = GL_LEQUAL,
        Greater         = GL_GREATER,
        NotEqual        = GL_NOTEQUAL,
        GreaterEqual    = GL_GEQUAL,
        Always          = GL_ALWAYS
    };

    enum class StencilFunction {
        Never           = GL_NEVER,
        Less            = GL_LESS,
        Equal           = GL_EQUAL,
        LessEqual       = GL_LEQUAL,
        Greater         = GL_GREATER,
        NotEqual        = GL_NOTEQUAL,
        GreaterEqual    = GL_GEQUAL,
        Always          = GL_ALWAYS
    };

    enum class StencilOperation {
        Keep            = GL_KEEP,
        Zero            = GL_ZERO,
        Replace         = GL_REPLACE,
        Increment       = GL_INCR,
        IncrementWrap   = GL_INCR_WRAP,
        Decrement       = GL_DECR,
        DecrementWrap   = GL_DECR_WRAP,
        Invert          = GL_INVERT
    };

    enum class PolygonMode {
        Point           = GL_POINT,
        Line            = GL_LINE,
        Fill            = GL_FILL
    };

    class RenderCommand {
    public:
        // Initialization
        static void Init();
        static void Shutdown();

        // Viewport and scissor
        static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
        static void SetScissor(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
        static void EnableScissor(bool enabled);

        // Clear operations
        static void SetClearColor(const glm::vec4& color);
        static void SetClearDepth(float depth);
        static void SetClearStencil(int stencil);
        static void Clear(ClearBufferMask mask = ClearBufferMask::Color | ClearBufferMask::Depth);

        // Drawing commands
        static void DrawArrays(DrawMode mode, uint32_t first, uint32_t count);
        static void DrawIndexed(DrawMode mode, uint32_t indexCount, uint32_t indexOffset, uint32_t baseVertex);
        static void DrawArraysInstanced(DrawMode mode, uint32_t first, uint32_t count, uint32_t instanceCount);
        static void DrawIndexedInstanced(DrawMode mode, uint32_t indexCount, uint32_t indexOffset, uint32_t baseVertex, uint32_t instanceCount);
        static void DrawIndirect(DrawMode mode, const void *indirect);
        static void DrawIndexedIndirect(DrawMode mode, const void *indirect);

        // Depth testing
        static void EnableDepthTest(bool enabled);
        static void SetDepthFunction(DepthFunction func);
        static void SetDepthMask(bool writeEnabled);

        // Blending
        static void EnableBlend(bool enabled);
        static void SetBlendFunction(BlendFunction src, BlendFunction dst);
        static void SetBlendFunctionSeparate(BlendFunction srcRGB, BlendFunction dstRGB,
                                             BlendFunction srcAlpha, BlendFunction dstAlpha);
        static void SetBlendEquation(BlendEquation equation);
        static void SetBlendEquationSeparate(BlendEquation rgb, BlendEquation alpha);
        static void SetBlendColor(const glm::vec4& color);

        // Stencil testing
        static void EnableStencil(bool enabled);
        static void SetStencilFunction(StencilFunction func, int ref, uint32_t mask);
        static void SetStencilOperation(StencilOperation fail, StencilOperation zfail, StencilOperation zpass);
        static void SetStencilMask(uint32_t mask);

        // Face culling
        static void EnableCullFace(bool enabled);
        static void SetCullFaceMode(CullFaceMode mode);
        static void SetFrontFace(bool clockwise = false);

        // Polygon mode and line width
        static void SetPolygonMode(PolygonMode mode);
        static void SetLineWidth(float width);
        static void SetPointSize(float size);

        // Multisampling
        static void EnableMultisample(bool enabled);

        // Color mask
        static void SetColorMask(bool r, bool g, bool b, bool a);

        // Wireframe mode
        static void EnableWireframe(bool enabled);

        // Query capabilities
        static int GetMaxTextureSize();
        static int GetMaxTextureUnits();
        static int GetMaxVertexAttributes();
        static std::string GetRenderer();
        static std::string GetVersion();
        static std::string GetVendor();

        // Debug and error handling
        static void CheckErrors(const std::string& location = "");
        static void PushDebugGroup(const std::string& name);
        static void PopDebugGroup();

    private:
        static void APIENTRY GLDebugCallback(GLenum source,
                                             GLenum type,
                                             GLuint id,
                                             GLenum severity,
                                             GLsizei length,
                                             const GLchar* message,
                                             const void* userParam);
    };

}

#endif //PIXLENGINE_RENDERCOMMAND_H