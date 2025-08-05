//
// Created by ChiroYuki on 05/08/2025.
//

#include "Pixl/Rendering/Camera/Controller/BaseCameraController.h"

namespace Pixl {

    glm::vec2 BaseCameraController::getMouseDelta(const MouseMovedEvent& e) {
        glm::vec2 currentPos(e.getX(), e.getY());

        if (firstMouse) {
            lastMousePos = currentPos;
            firstMouse = false;
            return glm::vec2(0.0f);
        }

        glm::vec2 delta = currentPos - lastMousePos;
        lastMousePos = currentPos;

        if (invertY) {
            delta.y = -delta.y;
        }

        return delta * mouseSensitivity;
    }

    bool BaseCameraController::isKeyPressed(int keyCode) const {
        auto it = keyStates.find(keyCode);
        return it != keyStates.end() && it->second;
    }

    void BaseCameraController::updateKeyState(int keyCode, bool pressed) {
        keyStates[keyCode] = pressed;
    }

    void BaseCameraController::reset() {
        firstMouse = true;
        keyStates.clear();
    }

}