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
        std::string Title;
        unsigned int Width;
        unsigned int Height;

        WindowProperties(std::string  title = "Pixl Engine",
                         unsigned int width = 1280,
                         unsigned int height = 720)
                : Title(std::move(title)), Width(width), Height(height) {}
    };

    class Window {
    public:
        using EventCallbackFunction = std::function<void(Event&)>;

        Window(const WindowProperties& props);
        ~Window();

        void onUpdate();

        unsigned int getWidth() const { return m_Data.Width; }
        unsigned int getHeight() const { return m_Data.Height; }
        float getAspectRatio() const { return static_cast<float>(m_Data.Width) / static_cast<float>(m_Data.Height); }

        void setEventCallback(const EventCallbackFunction& callback) { m_Data.EventCallback = callback; }
        void setVSync(bool enabled);
        bool isVSync() const;

        void* getNativeWindow() const { return m_Window; }
    private:
        void init(const WindowProperties& props);
        void shutdown();

    private:
        GLFWwindow* m_Window;
        Scope<GraphicsContext> m_Context;

        struct WindowData
        {
            std::string Title;
            unsigned int Width, Height;
            bool VSync;

            EventCallbackFunction EventCallback;
        };

        WindowData m_Data;
    };
}

#endif //PIXLENGINE_WINDOW_H
