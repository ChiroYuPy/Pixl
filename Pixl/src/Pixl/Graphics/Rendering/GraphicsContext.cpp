//
// Created by ChiroYuki on 26/07/2025.
//

#include "Pixl/Graphics/Rendering/GraphicsContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Pixl {

    GraphicsContext::GraphicsContext(GLFWwindow* windowHandle)
            : m_WindowHandle(windowHandle)
    {}

    void GraphicsContext::Init() {
        glfwMakeContextCurrent(m_WindowHandle);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }

    void GraphicsContext::SwapBuffers() {
        glfwSwapBuffers(m_WindowHandle);
    }

}