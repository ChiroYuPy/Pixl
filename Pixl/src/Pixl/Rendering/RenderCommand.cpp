//
// Created by ChiroYuki on 01/08/2025.
//

#include <iostream>
#include "Pixl/Rendering/RenderCommand.h"

namespace Pixl {

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
        if ((mask & ClearBufferMask::Color) == ClearBufferMask::Color) result |= GL_COLOR_BUFFER_BIT;
        if ((mask & ClearBufferMask::Depth) == ClearBufferMask::Depth) result |= GL_DEPTH_BUFFER_BIT;
        if ((mask & ClearBufferMask::Stencil) == ClearBufferMask::Stencil) result |= GL_STENCIL_BUFFER_BIT;
        return result;
    }

    static GLenum CullFaceModeToGL(CullFaceMode mode) {
        switch (mode) {
            case CullFaceMode::Front:         return GL_FRONT;
            case CullFaceMode::Back:          return GL_BACK;
            case CullFaceMode::FrontAndBack:  return GL_FRONT_AND_BACK;
        }
        return GL_BACK; // fallback
    }

    void OpenGLMessageCallback(
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

    void RenderCommand::Init() {

#ifdef PIXL_DEBUG
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(OpenGLMessageCallback, nullptr);

        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);
#endif

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LINE_SMOOTH);
    }

    void RenderCommand::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
        glViewport(static_cast<GLint>(x), static_cast<GLint>(y), static_cast<GLint>(width), static_cast<GLint>(height));
    }

    void RenderCommand::SetClearColor(const glm::vec4 &color) {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void RenderCommand::Clear(ClearBufferMask mask) {
        glClear(ClearMaskToGL(mask));
    }

    void RenderCommand::DrawIndexed(const Ref<VertexArray>& vertexArray, DrawMode mode, uint32_t indexCount) {
        vertexArray->bind();
        uint32_t count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetCount();
        glDrawElements(DrawModeToGL(mode), static_cast<GLsizei>(count), GL_UNSIGNED_INT, nullptr);
    }

    void RenderCommand::DrawArrays(const Ref<VertexArray>& vertexArray, DrawMode mode, uint32_t vertexCount) {
        vertexArray->bind();
        glDrawArrays(DrawModeToGL(mode), 0, static_cast<GLsizei>(vertexCount));
    }

    void RenderCommand::EnableDepthTest(bool enabled) {
        if (enabled) {
            glEnable(GL_DEPTH_TEST);
        } else {
            glDisable(GL_DEPTH_TEST);
        }
    }

    void RenderCommand::EnableBlend(bool enabled) {
        if (enabled) {
            glEnable(GL_BLEND);
        } else {
            glDisable(GL_BLEND);
        }
    }

    void RenderCommand::EnableCullFace(bool enabled) {
        if (enabled) {
            glEnable(GL_CULL_FACE);
        } else {
            glDisable(GL_CULL_FACE);
        }
    }

    void RenderCommand::SetLineWidth(float width) {
        glLineWidth(width);
    }

    void RenderCommand::SetCullFaceMode(CullFaceMode mode) {
        glCullFace(CullFaceModeToGL(mode));
    }

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

}