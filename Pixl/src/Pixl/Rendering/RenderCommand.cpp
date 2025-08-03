//
// Created by ChiroYuki on 01/08/2025.
//

#include <iostream>
#include "Pixl/Rendering/RenderCommand.h"

namespace Pixl {

    // Helper functions to convert enums to OpenGL constants
    static GLenum DrawModeToGL(DrawMode mode) {
        switch (mode) {
            case DrawMode::Points:        return GL_POINTS;
            case DrawMode::Lines:         return GL_LINES;
            case DrawMode::LineStrip:     return GL_LINE_STRIP;
            case DrawMode::LineLoop:      return GL_LINE_LOOP;
            case DrawMode::Triangles:     return GL_TRIANGLES;
            case DrawMode::TriangleStrip: return GL_TRIANGLE_STRIP;
            case DrawMode::TriangleFan:   return GL_TRIANGLE_FAN;
        }
        return GL_TRIANGLES;
    }

    static GLbitfield ClearMaskToGL(ClearBufferMask mask) {
        GLbitfield result = 0;
        if ((mask & ClearBufferMask::Color) == ClearBufferMask::Color)     result |= GL_COLOR_BUFFER_BIT;
        if ((mask & ClearBufferMask::Depth) == ClearBufferMask::Depth)     result |= GL_DEPTH_BUFFER_BIT;
        if ((mask & ClearBufferMask::Stencil) == ClearBufferMask::Stencil) result |= GL_STENCIL_BUFFER_BIT;
        return result;
    }

    static GLenum CullFaceModeToGL(CullFaceMode mode) {
        switch (mode) {
            case CullFaceMode::Front:        return GL_FRONT;
            case CullFaceMode::Back:         return GL_BACK;
            case CullFaceMode::FrontAndBack: return GL_FRONT_AND_BACK;
        }
        return GL_BACK; // fallback
    }

    static GLenum BlendFunctionToGL(BlendFunction func) {
        return static_cast<GLenum>(func);
    }

    static GLenum BlendEquationToGL(BlendEquation equation) {
        return static_cast<GLenum>(equation);
    }

    static GLenum DepthFunctionToGL(DepthFunction func) {
        return static_cast<GLenum>(func);
    }

    static GLenum StencilFunctionToGL(StencilFunction func) {
        return static_cast<GLenum>(func);
    }

    static GLenum StencilOperationToGL(StencilOperation op) {
        return static_cast<GLenum>(op);
    }

    static GLenum PolygonModeToGL(PolygonMode mode) {
        return static_cast<GLenum>(mode);
    }

    void RenderCommand::OpenGLMessageCallback(
            unsigned source,
            unsigned type,
            unsigned id,
            unsigned severity,
            int length,
            const char* message,
            const void* userParam)
    {
        std::cerr << "[OpenGL Debug Message] (" << id << "): " << message << "\n";

        switch (severity) {
            case GL_DEBUG_SEVERITY_HIGH:         std::cerr << "Severity: HIGH\n"; break;
            case GL_DEBUG_SEVERITY_MEDIUM:       std::cerr << "Severity: MEDIUM\n"; break;
            case GL_DEBUG_SEVERITY_LOW:          std::cerr << "Severity: LOW\n"; break;
            case GL_DEBUG_SEVERITY_NOTIFICATION: std::cerr << "Severity: NOTIFICATION\n"; break;
        }

        std::cerr << std::endl;
    }

    // Initialization
    void RenderCommand::Init() {
#ifdef PIXL_DEBUG
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(OpenGLMessageCallback, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);
#endif

        EnableBlend(true);
        SetBlendFunction(BlendFunction::SrcAlpha, BlendFunction::OneMinusSrcAlpha);

        EnableDepthTest(true);
        Pixl::RenderCommand::SetDepthFunction(Pixl::DepthFunction::Less);
        glEnable(GL_LINE_SMOOTH);
    }

    void RenderCommand::Shutdown() {
        // Cleanup if needed
    }

    // Viewport and scissor
    void RenderCommand::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
        glViewport(static_cast<GLint>(x), static_cast<GLint>(y), static_cast<GLint>(width), static_cast<GLint>(height));
    }

    void RenderCommand::SetScissor(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
        glScissor(static_cast<GLint>(x), static_cast<GLint>(y), static_cast<GLint>(width), static_cast<GLint>(height));
    }

    void RenderCommand::EnableScissor(bool enabled) {
        if (enabled) {
            glEnable(GL_SCISSOR_TEST);
        } else {
            glDisable(GL_SCISSOR_TEST);
        }
    }

    // Clear operations
    void RenderCommand::SetClearColor(const glm::vec4 &color) {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void RenderCommand::SetClearDepth(float depth) {
        glClearDepth(depth);
    }

    void RenderCommand::SetClearStencil(int stencil) {
        glClearStencil(stencil);
    }

    void RenderCommand::Clear(ClearBufferMask mask) {
        glClear(ClearMaskToGL(mask));
    }

    /**
     * @brief Renders primitives from vertex array data without using indices
     *
     * This is the simplest draw call, reading vertices sequentially from the
     * currently bound vertex buffers. Best for simple geometry or when vertex
     * reuse is minimal.
     *
     * @param mode The primitive type to render (triangles, lines, points, etc.)
     * @param first Starting vertex index in the vertex arrays
     * @param count Number of vertices to render
     *
     * @note Requires vertex buffers to be bound to the current VAO
     * @note No index buffer is used - vertices are processed in sequential order
     *
     * Example:
     * @code
     * // Render a triangle using vertices 0, 1, 2
     * RenderCommand::DrawArrays(DrawMode::Triangles, 0, 3);
     *
     * // Render second triangle using vertices 3, 4, 5
     * RenderCommand::DrawArrays(DrawMode::Triangles, 3, 3);
     * @endcode
     */
    void RenderCommand::DrawArrays(DrawMode mode, uint32_t first, uint32_t count) {
        glDrawArrays(DrawModeToGL(mode), static_cast<GLint>(first), static_cast<GLsizei>(count));
    }

    /**
     * @brief Renders primitives using an index buffer for vertex reuse
     *
     * Most efficient method for rendering complex geometry where vertices are
     * shared between multiple primitives. Uses indices to reference vertices,
     * allowing significant memory savings and better cache performance.
     *
     * @param mode The primitive type to render (triangles, lines, points, etc.)
     * @param indexCount Number of indices to process from the index buffer
     * @param indexOffset Starting position in the index buffer (in indices, not bytes)
     * @param baseVertex Value added to each index before vertex lookup (for multi-object buffers)
     *
     * @note Requires both vertex buffers and an index buffer bound to current VAO
     * @note Index buffer must contain uint32_t indices
     * @note When baseVertex > 0, uses glDrawElementsBaseVertex for better performance
     *
     * Example:
     * @code
     * // Render a quad using indices [0,1,2, 2,1,3] starting from index 0
     * RenderCommand::DrawIndexed(DrawMode::Triangles, 6, 0, 0);
     *
     * // Render second object stored at vertices 100+ using same index pattern
     * RenderCommand::DrawIndexed(DrawMode::Triangles, 6, 0, 100);
     *
     * // Render using indices starting at position 12 in index buffer
     * RenderCommand::DrawIndexed(DrawMode::Triangles, 6, 12, 0);
     * @endcode
     */
    void RenderCommand::DrawIndexed(DrawMode mode, uint32_t indexCount, uint32_t indexOffset, uint32_t baseVertex) {
        if (baseVertex > 0) {
            glDrawElementsBaseVertex(DrawModeToGL(mode), static_cast<GLsizei>(indexCount), GL_UNSIGNED_INT,
                                     (const void*)(uintptr_t)(indexOffset * sizeof(uint32_t)),
                                     static_cast<GLint>(baseVertex));
        } else {
            glDrawElements(DrawModeToGL(mode), static_cast<GLsizei>(indexCount), GL_UNSIGNED_INT,
                           (const void*)(uintptr_t)(indexOffset * sizeof(uint32_t)));
        }
    }

    /**
     * @brief Renders multiple instances of the same geometry in a single draw call
     *
     * Highly efficient method for rendering many copies of identical geometry
     * (trees, particles, grass, etc.). Each instance can have different properties
     * via instance attributes or gl_InstanceID in shaders.
     *
     * @param mode The primitive type to render (triangles, lines, points, etc.)
     * @param first Starting vertex index in the vertex arrays
     * @param count Number of vertices per instance
     * @param instanceCount Number of instances to render
     *
     * @note Vertex shader receives gl_InstanceID built-in variable
     * @note Instance-specific data should be provided via instanced vertex attributes
     * @note All instances share the same vertex data but can have different transforms/colors
     *
     * Example:
     * @code
     * // Render 1000 copies of a triangle (vertices 0,1,2)
     * RenderCommand::DrawArraysInstanced(DrawMode::Triangles, 0, 3, 1000);
     *
     * // Vertex shader can use gl_InstanceID to differentiate instances:
     * // vec3 position = basePosition + instanceOffsets[gl_InstanceID];
     * @endcode
     */
    void RenderCommand::DrawArraysInstanced(DrawMode mode, uint32_t first, uint32_t count, uint32_t instanceCount) {
        glDrawArraysInstanced(DrawModeToGL(mode), static_cast<GLint>(first),
                              static_cast<GLsizei>(count), static_cast<GLsizei>(instanceCount));
    }

    /**
     * @brief Renders multiple instances of indexed geometry in a single draw call
     *
     * Combines the benefits of indexed rendering (vertex reuse) with instancing
     * (multiple copies). Most efficient method for rendering many complex objects
     * that share the same topology but have different properties.
     *
     * @param mode The primitive type to render (triangles, lines, points, etc.)
     * @param indexCount Number of indices to process per instance
     * @param indexOffset Starting position in the index buffer (in indices, not bytes)
     * @param baseVertex Value added to each index before vertex lookup
     * @param instanceCount Number of instances to render
     *
     * @note Combines all benefits of DrawIndexed and DrawArraysInstanced
     * @note Perfect for rendering multiple complex meshes (buildings, vehicles, etc.)
     * @note Each instance can have different transforms via instance attributes
     *
     * Example:
     * @code
     * // Render 500 copies of a complex mesh using indices 0-299
     * RenderCommand::DrawIndexedInstanced(DrawMode::Triangles, 300, 0, 0, 500);
     *
     * // Render multiple objects from a batch, each with 150 indices
     * // Object 1: vertices 0-99,   indices 0-149
     * // Object 2: vertices 100-199, indices 0-149 (reused pattern)
     * RenderCommand::DrawIndexedInstanced(DrawMode::Triangles, 150, 0, 0, 1);    // Object 1
     * RenderCommand::DrawIndexedInstanced(DrawMode::Triangles, 150, 0, 100, 1);  // Object 2
     * @endcode
     */
    void RenderCommand::DrawIndexedInstanced(DrawMode mode, uint32_t indexCount, uint32_t indexOffset, uint32_t baseVertex, uint32_t instanceCount) {
        if (baseVertex > 0) {
            glDrawElementsInstancedBaseVertex(DrawModeToGL(mode), static_cast<GLsizei>(indexCount),
                                              GL_UNSIGNED_INT, (const void*)(uintptr_t)(indexOffset * sizeof(uint32_t)),
                                              static_cast<GLsizei>(instanceCount), static_cast<GLint>(baseVertex));
        } else {
            glDrawElementsInstanced(DrawModeToGL(mode), static_cast<GLsizei>(indexCount), GL_UNSIGNED_INT,
                                    (const void*)(uintptr_t)(indexOffset * sizeof(uint32_t)),
                                    static_cast<GLsizei>(instanceCount));
        }
    }

    void RenderCommand::DrawIndirect(DrawMode mode, const void* indirect) {
        glDrawArraysIndirect(DrawModeToGL(mode), indirect);
    }

    void RenderCommand::DrawIndexedIndirect(DrawMode mode, const void* indirect) {
        glDrawElementsIndirect(DrawModeToGL(mode), GL_UNSIGNED_INT, indirect);
    }

    // Depth testing
    void RenderCommand::EnableDepthTest(bool enabled) {
        if (enabled) {
            glEnable(GL_DEPTH_TEST);
        } else {
            glDisable(GL_DEPTH_TEST);
        }
    }

    void RenderCommand::SetDepthFunction(DepthFunction func) {
        glDepthFunc(DepthFunctionToGL(func));
    }

    void RenderCommand::SetDepthMask(bool writeEnabled) {
        glDepthMask(writeEnabled ? GL_TRUE : GL_FALSE);
    }

    // Blending
    void RenderCommand::EnableBlend(bool enabled) {
        if (enabled) {
            glEnable(GL_BLEND);
        } else {
            glDisable(GL_BLEND);
        }
    }

    void RenderCommand::SetBlendFunction(BlendFunction src, BlendFunction dst) {
        glBlendFunc(BlendFunctionToGL(src), BlendFunctionToGL(dst));
    }

    void RenderCommand::SetBlendFunctionSeparate(BlendFunction srcRGB, BlendFunction dstRGB,
                                                 BlendFunction srcAlpha, BlendFunction dstAlpha) {
        glBlendFuncSeparate(BlendFunctionToGL(srcRGB), BlendFunctionToGL(dstRGB),
                            BlendFunctionToGL(srcAlpha), BlendFunctionToGL(dstAlpha));
    }

    void RenderCommand::SetBlendEquation(BlendEquation equation) {
        glBlendEquation(BlendEquationToGL(equation));
    }

    void RenderCommand::SetBlendEquationSeparate(BlendEquation rgb, BlendEquation alpha) {
        glBlendEquationSeparate(BlendEquationToGL(rgb), BlendEquationToGL(alpha));
    }

    void RenderCommand::SetBlendColor(const glm::vec4& color) {
        glBlendColor(color.r, color.g, color.b, color.a);
    }

    // Stencil testing
    void RenderCommand::EnableStencil(bool enabled) {
        if (enabled) {
            glEnable(GL_STENCIL_TEST);
        } else {
            glDisable(GL_STENCIL_TEST);
        }
    }

    void RenderCommand::SetStencilFunction(StencilFunction func, int ref, uint32_t mask) {
        glStencilFunc(StencilFunctionToGL(func), ref, mask);
    }

    void RenderCommand::SetStencilOperation(StencilOperation fail, StencilOperation zfail, StencilOperation zpass) {
        glStencilOp(StencilOperationToGL(fail), StencilOperationToGL(zfail), StencilOperationToGL(zpass));
    }

    void RenderCommand::SetStencilMask(uint32_t mask) {
        glStencilMask(mask);
    }

    // Face culling
    void RenderCommand::EnableCullFace(bool enabled) {
        if (enabled) {
            glEnable(GL_CULL_FACE);
        } else {
            glDisable(GL_CULL_FACE);
        }
    }

    void RenderCommand::SetCullFaceMode(CullFaceMode mode) {
        glCullFace(CullFaceModeToGL(mode));
    }

    void RenderCommand::SetFrontFace(bool clockwise) {
        glFrontFace(clockwise ? GL_CW : GL_CCW);
    }

    // Polygon mode and line width
    void RenderCommand::SetPolygonMode(PolygonMode mode) {
        glPolygonMode(GL_FRONT_AND_BACK, PolygonModeToGL(mode));
    }

    void RenderCommand::SetLineWidth(float width) {
        glLineWidth(width);
    }

    void RenderCommand::SetPointSize(float size) {
        glPointSize(size);
    }

    // Multisampling
    void RenderCommand::EnableMultisample(bool enabled) {
        if (enabled) {
            glEnable(GL_MULTISAMPLE);
        } else {
            glDisable(GL_MULTISAMPLE);
        }
    }

    // Color mask
    void RenderCommand::SetColorMask(bool r, bool g, bool b, bool a) {
        glColorMask(r ? GL_TRUE : GL_FALSE, g ? GL_TRUE : GL_FALSE,
                    b ? GL_TRUE : GL_FALSE, a ? GL_TRUE : GL_FALSE);
    }

    // Wireframe mode
    void RenderCommand::EnableWireframe(bool enabled) {
        if (enabled) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        } else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
    }

    // Query capabilities
    int RenderCommand::GetMaxTextureSize() {
        GLint maxSize;
        glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxSize);
        return static_cast<int>(maxSize);
    }

    int RenderCommand::GetMaxTextureUnits() {
        GLint maxUnits;
        glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxUnits);
        return static_cast<int>(maxUnits);
    }

    int RenderCommand::GetMaxVertexAttributes() {
        GLint maxAttribs;
        glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxAttribs);
        return static_cast<int>(maxAttribs);
    }

    std::string RenderCommand::GetRenderer() {
        const char* renderer = reinterpret_cast<const char*>(glGetString(GL_RENDERER));
        return renderer ? std::string(renderer) : "Unknown";
    }

    std::string RenderCommand::GetVersion() {
        const char* version = reinterpret_cast<const char*>(glGetString(GL_VERSION));
        return version ? std::string(version) : "Unknown";
    }

    std::string RenderCommand::GetVendor() {
        const char* vendor = reinterpret_cast<const char*>(glGetString(GL_VENDOR));
        return vendor ? std::string(vendor) : "Unknown";
    }

    // Debug and error handling
    void RenderCommand::CheckErrors(const std::string& location) {
        GLenum err;
        while ((err = glGetError()) != GL_NO_ERROR) {
            std::cerr << "[OpenGL Error] ";
            if (!location.empty()) {
                std::cerr << "at " << location << " : ";
            }
            switch (err) {
                case GL_INVALID_ENUM:                  std::cerr << "GL_INVALID_ENUM"; break;
                case GL_INVALID_VALUE:                 std::cerr << "GL_INVALID_VALUE"; break;
                case GL_INVALID_OPERATION:             std::cerr << "GL_INVALID_OPERATION"; break;
                case GL_STACK_OVERFLOW:                std::cerr << "GL_STACK_OVERFLOW"; break;
                case GL_STACK_UNDERFLOW:               std::cerr << "GL_STACK_UNDERFLOW"; break;
                case GL_OUT_OF_MEMORY:                 std::cerr << "GL_OUT_OF_MEMORY"; break;
                case GL_INVALID_FRAMEBUFFER_OPERATION: std::cerr << "GL_INVALID_FRAMEBUFFER_OPERATION"; break;
                default:                             std::cerr << "Unknown error (" << err << ")"; break;
            }
            std::cerr << std::endl;
        }
    }

    void RenderCommand::PushDebugGroup(const std::string& name) {
#ifdef PIXL_DEBUG
        glPushDebugGroup(GL_DEBUG_SOURCE_APPLICATION, 0, static_cast<GLsizei>(name.length()), name.c_str());
#endif
    }

    void RenderCommand::PopDebugGroup() {
#ifdef PIXL_DEBUG
        glPopDebugGroup();
#endif
    }

}