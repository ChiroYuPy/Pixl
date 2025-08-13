//
// Created by ChiroYuki on 26/07/2025.
//

#include "Pixl/Rendering/GraphicsContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

namespace Pixl {

    GraphicsContext::GraphicsContext(GLFWwindow* windowHandle)
            : m_windowHandle(windowHandle)
    {}

    void GraphicsContext::Init() {
        glfwMakeContextCurrent(m_windowHandle);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback([](GLenum source, GLenum type, GLuint id,
                                  GLenum severity, GLsizei length,
                                  const GLchar* message, const void* userParam) {
            std::cerr << "[OpenGL Debug] Source: " << source
                      << ", Type: " << type
                      << ", Severity: " << severity
                      << ", ID: " << id
                      << "\nMessage: " << message << std::endl;
        }, nullptr);
    }

    void GraphicsContext::SwapBuffers() {
        glfwSwapBuffers(m_windowHandle);
    }

}