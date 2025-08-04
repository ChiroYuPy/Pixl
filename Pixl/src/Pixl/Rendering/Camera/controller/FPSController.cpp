//
// Created by ChiroYuki on 04/08/2025.
//

#include "Pixl/Rendering/Camera/Controller/FPSController.h"

namespace Pixl {

    bool FPSController::onMouseMoved(Pixl::MouseMovedEvent e) {
        static bool firstMouse = true;
        static float lastX = 0.0f;
        static float lastY = 0.0f;

        float x = e.getX();
        float y = e.getY();

        if (firstMouse) {
            lastX = x;
            lastY = y;
            firstMouse = false;
            return false;  // ignore le premier mouvement
        }

        float dx = (x - lastX) * sensitivity;
        float dy = (y - lastY) * sensitivity;

        lastX = x;
        lastY = y;

        yaw -= dx;
        pitch -= dy;

        // Clamp le pitch pour éviter les flips
        pitch = glm::clamp(pitch, -90.0f, 90.0f);

        // Construit la rotation finale
        glm::quat qPitch = glm::angleAxis(glm::radians(pitch), glm::vec3(1, 0, 0));
        glm::quat qYaw   = glm::angleAxis(glm::radians(yaw),   glm::vec3(0, 1, 0));
        glm::quat orientation = qYaw * qPitch;

        camera->setOrientation(orientation);

        return true;
    }

}