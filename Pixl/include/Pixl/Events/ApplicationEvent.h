//
// Created by ChiroYuki on 26/07/2025.
//

#ifndef PIXLENGINE_APPLICATIONEVENTS_H
#define PIXLENGINE_APPLICATIONEVENTS_H

#include "Pixl/Events/Event.h"

namespace Pixl {
    class WindowResizeEvent : public Event {
    public:
        WindowResizeEvent(unsigned int width, unsigned int height, float aspectRatio)
                : m_width(width), m_height(height), m_aspectRatio(aspectRatio) {}

        unsigned int getWidth() const { return m_width; }
        unsigned int getHeight() const { return m_height; }
        float getAspectRatio() const { return m_aspectRatio; }

        std::string toString() const override {
            std::stringstream ss;
            ss << "WindowResizeEvent: (width=" << m_width << ") (height=" << m_height << ") (aspectRatio=" << m_aspectRatio << ")";
            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowResize)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)

    private:
        unsigned int m_width, m_height;
        float m_aspectRatio;
    };

    class WindowFocusEvent : public Event {
    public:
        explicit WindowFocusEvent(bool focused) : m_focused(focused) {}

        bool isFocused() const { return m_focused; }

        std::string toString() const override {
            std::stringstream ss;
            ss << "WindowFocusEvent: (focused=" << (m_focused ? "true" : "false") << ")";
            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowFocus)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)

    private:
        bool m_focused;
    };

    class WindowMovedEvent : public Event {
    public:
        WindowMovedEvent(int x, int y) : m_x(x), m_y(y) {}

        int getX() const { return m_x; }
        int getY() const { return m_y; }

        std::string toString() const override {
            std::stringstream ss;
            ss << "WindowMovedEvent: (x=" << m_x << ") (y=" << m_y << ")";
            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowMoved)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)

    private:
        int m_x, m_y;
    };

    class WindowCloseEvent : public Event {
    public:
        WindowCloseEvent() = default;

        EVENT_CLASS_TYPE(WindowClose)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class AppTickEvent : public Event {
    public:
        AppTickEvent() = default;

        EVENT_CLASS_TYPE(AppTick)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class AppUpdateEvent : public Event {
    public:
        AppUpdateEvent() = default;

        EVENT_CLASS_TYPE(AppUpdate)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class AppRenderEvent : public Event {
    public:
        AppRenderEvent() = default;

        EVENT_CLASS_TYPE(AppRender)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };
}

#endif //PIXLENGINE_APPLICATIONEVENTS_H
