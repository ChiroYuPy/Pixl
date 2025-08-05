//
// Created by ChiroYuki on 26/07/2025.
//

#ifndef PIXLENGINE_WINDOW_H
#define PIXLENGINE_WINDOW_H

#include "Pixl/Core/Base.h"
#include "Pixl/Rendering/GraphicsContext.h"
#include "Pixl/Events/Event.h"
#include "Pixl/Events/ApplicationEvent.h"
#include "Pixl/Events/WindowEvent.h"
#include "Pixl/Events/KeyEvent.h"
#include "Pixl/Events/MouseEvent.h"

#include <functional>
#include <string>
#include <cstdint>
#include <utility>

struct GLFWwindow;

namespace Pixl {

    enum class WindowMode {
        Windowed,           // Standard window with borders and title bar
        Fullscreen,         // Exclusive fullscreen mode (may change resolution)
        Borderless,         // Window without borders or title bar (borderless window)
        FullscreenWindowed, // Borderless fullscreen window (covers entire screen without changing resolution)
        TransparentOverlay  // Transparent window with alpha channel (overlay on top of other windows)
    };

    enum class WindowFlags : uint32_t {
        None         = 0,
        Resizable    = 1u << 0,
        Decorated    = 1u << 1,
        Floating     = 1u << 2,
        Transparent  = 1u << 3
    };

    constexpr WindowFlags operator|(WindowFlags a, WindowFlags b) noexcept {
        return static_cast<WindowFlags>(std::underlying_type_t<WindowFlags>(a) |
                                        std::underlying_type_t<WindowFlags>(b));
    }

    constexpr WindowFlags operator&(WindowFlags a, WindowFlags b) noexcept {
        return static_cast<WindowFlags>(std::underlying_type_t<WindowFlags>(a) &
                                        std::underlying_type_t<WindowFlags>(b));
    }

    constexpr bool any(WindowFlags f) noexcept {
        return std::underlying_type_t<WindowFlags>(f) != 0;
    }

    struct WindowProperties
    {
        std::string title;
        uint32_t width;
        uint32_t height;
        WindowMode mode;
        WindowFlags flags;

        WindowProperties(std::string title = "Pixl Engine",
                         uint32_t width = 1280,
                         uint32_t height = 720,
                         WindowMode mode = WindowMode::Windowed,
                         WindowFlags flags = WindowFlags::Resizable | WindowFlags::Decorated)
                         : title(std::move(title)), width(width), height(height), mode(mode), flags(flags) {}
    };

    class Window {
    public:
        using EventCallbackFunction = std::function<void(Event&)>;

        Window(const WindowProperties& props);
        ~Window();

        void onUpdate();

        uint32_t getWidth() const { return m_data.width; }
        uint32_t getHeight() const { return m_data.height; }
        float getAspectRatio() const { return m_data.aspectRatio; }

        void* getNativeWindow() const { return m_windowHandle; }

        void setEventCallback(const EventCallbackFunction& callback) { m_data.eventCallback = callback; }

        void setVSync(bool enabled);
        bool isVSync() const;

    private:
        void init(const WindowProperties& props);
        void shutdown();

        void applyHints(WindowFlags flags, WindowMode mode);
        void setupCallbacks();

    private:
        GLFWwindow* m_windowHandle;
        Scope<GraphicsContext> m_context;

        struct WindowData {
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
