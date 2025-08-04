//
// Created by ChiroYuki on 26/07/2025.
//

#ifndef PIXLENGINE_MOUSEEVENT_H
#define PIXLENGINE_MOUSEEVENT_H

#include "Pixl/Events/Event.h"
#include "Pixl/Core/MouseCodes.h"

namespace Pixl {

    class MouseMovedEvent : public Event
    {
    public:
        MouseMovedEvent(const float x, const float y, const float dx, const float dy)
                : m_MouseX(x), m_MouseY(y), m_DeltaX(dx), m_DeltaY(dy) {}

        float getX() const { return m_MouseX; }
        float getY() const { return m_MouseY; }
        float getDX() const { return m_DeltaX; }
        float getDY() const { return m_DeltaY; }

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseMoved)
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
    private:
        float m_MouseX, m_MouseY;
        float m_DeltaX, m_DeltaY;
    };

    class MouseScrolledEvent : public Event
    {
    public:
        MouseScrolledEvent(const float xOffset, const float yOffset)
                : m_XOffset(xOffset), m_YOffset(yOffset) {}

        float getXOffset() const { return m_XOffset; }
        float getYOffset() const { return m_YOffset; }

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "MouseScrolledEvent: " << getXOffset() << ", " << getYOffset();
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseScrolled)
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
    private:
        float m_XOffset, m_YOffset;
    };

    class MouseButtonEvent : public Event
    {
    public:
        MouseCode GetMouseButton() const { return m_Button; }

        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput | EventCategoryMouseButton)
    protected:
        MouseButtonEvent(const MouseCode button)
                : m_Button(button) {}

        MouseCode m_Button;
    };

    class MouseButtonPressedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonPressedEvent(const MouseCode button)
                : MouseButtonEvent(button) {}

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: " << m_Button;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonPressed)
    };

    class MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonReleasedEvent(const MouseCode button)
                : MouseButtonEvent(button) {}

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent: " << m_Button;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonReleased)
    };

}

#endif //PIXLENGINE_MOUSEEVENT_H
