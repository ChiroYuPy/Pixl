//
// Created by ChiroYuki on 26/07/2025.
//

#include "Pixl/Core/Window.h"
#include "Pixl/Events/ApplicationEvent.h"
#include "Pixl/Events/KeyEvent.h"
#include "Pixl/Events/MouseEvent.h"

namespace Pixl {

    static uint8_t s_GLFWWindowCount = 0;

    static void GLFWErrorCallback(int error, const char* description) {
        std::cout << "GLFW ERROR: " << error << " | " << description << std::endl;
    }

    Window::Window(const WindowProperties& props) : m_windowHandle() {
        init(props);
    }

    Window::~Window() {
        shutdown();
    }

    void Window::init(const WindowProperties& props) {
        m_data.title = props.title;
        m_data.width = props.width;
        m_data.height = props.height;

        if (s_GLFWWindowCount == 0)
        {
            int success = glfwInit();
            glfwSetErrorCallback(GLFWErrorCallback);
        }

        {
            m_windowHandle = glfwCreateWindow((int)props.width, (int)props.height, m_data.title.c_str(), nullptr, nullptr);
            ++s_GLFWWindowCount;
        }

        m_context = MakeScope<GraphicsContext>(m_windowHandle);
        m_context->Init();

        glfwSetWindowUserPointer(m_windowHandle, &m_data);
        setVSync(true);

        // Set GLFW callbacks
        glfwSetWindowSizeCallback(m_windowHandle, [](GLFWwindow* window, int width, int height)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            data.width = width;
            data.height = height;
            data.aspectRatio = static_cast<float>(data.width) / static_cast<float>(data.height);

            WindowResizeEvent event(width, height, data.aspectRatio);
            data.eventCallback(event);
        });

        glfwSetWindowCloseCallback(m_windowHandle, [](GLFWwindow* window)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            WindowCloseEvent event;
            data.eventCallback(event);
        });

        glfwSetKeyCallback(m_windowHandle, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
                case GLFW_PRESS:
                {
                    KeyPressedEvent event(static_cast<KeyCode>(key), 0, mods);
                    data.eventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent event(static_cast<KeyCode>(key), mods);
                    data.eventCallback(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent event(static_cast<KeyCode>(key), 1, mods);
                    data.eventCallback(event);
                    break;
                }
            }
        });

        glfwSetCharCallback(m_windowHandle, [](GLFWwindow* window, unsigned int keycode)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            KeyTypedEvent event(keycode);
            data.eventCallback(event);
        });

        glfwSetMouseButtonCallback(m_windowHandle, [](GLFWwindow* window, int button, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event(static_cast<MouseCode>(button), mods);
                    data.eventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent event(static_cast<MouseCode>(button), mods);
                    data.eventCallback(event);
                    break;
                }
            }
        });

        glfwSetCursorEnterCallback(m_windowHandle, [](GLFWwindow* window, int entered)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            MouseEnteredEvent event(entered == GLFW_TRUE);
            data.eventCallback(event);
        });

        glfwSetScrollCallback(m_windowHandle, [](GLFWwindow* window, double xOffset, double yOffset)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseScrolledEvent event((float)xOffset, (float)yOffset);
            data.eventCallback(event);
        });

        glfwSetCursorPosCallback(m_windowHandle, [](GLFWwindow* window, double xPos, double yPos)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseMovedEvent event((float)xPos, (float)yPos);
            data.eventCallback(event);
        });
    }

    void Window::shutdown() {
        glfwDestroyWindow(m_windowHandle);
        --s_GLFWWindowCount;

        if (s_GLFWWindowCount == 0)
        {
            glfwTerminate();
        }
    }

    void Window::onUpdate() {
        glfwPollEvents();
        m_context->SwapBuffers();
    }

    void Window::setVSync(bool enabled) {
        if (enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);

        m_data.verticalSynchronization = enabled;
    }

    bool Window::isVSync() const {
        return m_data.verticalSynchronization;
    }
}