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

    struct WindowSettings
    {
        std::string Title;
        unsigned int Width;
        unsigned int Height;

        WindowSettings(std::string  title = "Pixl Engine",
                       unsigned int width = 1280,
                       unsigned int height = 720)
                : Title(std::move(title)), Width(width), Height(height) {}
    };

    class Window {
    public:
        using EventCallbackFunction = std::function<void(Event&)>;

        Window(const WindowSettings& props);
        ~Window();

        void OnUpdate();

        unsigned int GetWidth() const { return m_Data.Width; }
        unsigned int GetHeight() const { return m_Data.Height; }
        float GetAspectRatio() const { return m_Data.Width / m_Data.Height; }

        void SetEventCallback(const EventCallbackFunction& callback) { m_Data.EventCallback = callback; }
        void SetVSync(bool enabled);
        bool IsVSync() const;

        void* GetNativeWindow() const { return m_Window; }
    private:
        void Init(const WindowSettings& props);
        void Shutdown();

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
