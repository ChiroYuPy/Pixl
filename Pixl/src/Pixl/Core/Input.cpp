//
// Created by ChiroYuki on 26/07/2025.
//

#include "Pixl/Core/Input.h"

#include "Pixl/Core/Application.h"
#include <GLFW/glfw3.h>

namespace Pixl {

    bool Input::isKeyPressed(KeyCode key) {
        auto* window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
        auto state = glfwGetKey(window, static_cast<int32_t>(key));
        return state == GLFW_PRESS;
    }

    bool Input::isMouseButtonPressed(MouseCode button) {
        auto* window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
        auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
        return state == GLFW_PRESS;
    }

    glm::vec2 Input::getMousePosition() {
        auto* window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
        double x, y;
        glfwGetCursorPos(window, &x, &y);

        return { (float)x, (float)y };
    }

}