//
// Created by ChiroYuki on 26/07/2025.
//

#ifndef PIXLENGINE_WINDOW_H
#define PIXLENGINE_WINDOW_H

#include "Pixl/Core/Base.h"
#include "Pixl/Events/Event.h"
#include "Pixl/Rendering/GraphicsContext.h"

#include <functional>
#include <string>
#include <cstdint>
#include <utility>
#include <GLFW/glfw3.h>

namespace Pixl {

    struct WindowProperties
    {
        std::string title;
        unsigned int width;
        unsigned int height;

        WindowProperties(std::string  title = "Pixl Engine",
                         unsigned int width = 1280,
                         unsigned int height = 720)
                : title(std::move(title)), width(width), height(height) {}
    };

    class Window {
    public:
        using EventCallbackFunction = std::function<void(Event&)>;

        Window(const WindowProperties& props);
        ~Window();

        void onUpdate();

        unsigned int getWidth() const { return m_data.width; }
        unsigned int getHeight() const { return m_data.height; }
        float getAspectRatio() const { return m_data.aspectRatio; }

        void setEventCallback(const EventCallbackFunction& callback) { m_data.eventCallback = callback; }
        void setVSync(bool enabled);
        bool isVSync() const;

        void* getNativeWindow() const { return m_windowHandle; }
    private:
        void init(const WindowProperties& props);
        void shutdown();

    private:
        GLFWwindow* m_windowHandle;
        Scope<GraphicsContext> m_context;

        struct WindowData
        {
            std::string title;
            unsigned int width, height;
            float aspectRatio;
            bool verticalSynchronization;

            EventCallbackFunction eventCallback;
        };

        WindowData m_data;
    };
}

#endif //PIXLENGINE_WINDOW_H
