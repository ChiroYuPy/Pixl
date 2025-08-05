//
// Created by ChiroYuki on 26/07/2025.
//

#ifndef PIXLENGINE_INPUT_H
#define PIXLENGINE_INPUT_H

#include "Pixl/Core/KeyCodes.h"
#include "Pixl/Core/MouseCodes.h"
#include "Application.h"

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

namespace Pixl {

    enum class CursorMode {
        Visible = GLFW_CURSOR_NORMAL,
        Hidden = GLFW_CURSOR_HIDDEN,
        Captured = GLFW_CURSOR_DISABLED
    };

    class Input {
    public:
        static bool isKeyPressed(KeyCode key);

        static bool isMouseButtonPressed(MouseCode button);
        static void setMousePosition(float x, float y);
        static glm::vec2 getMousePosition();

        static bool isWindowFocused();
        static bool isMouseInWindow();

        static void setCursorMode(CursorMode mode);
        static CursorMode getCursorMode();
    };

}

#endif //PIXLENGINE_INPUT_H
