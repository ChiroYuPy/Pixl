//
// Created by ChiroYuki on 04/08/2025.
//

#include "Pixl/Rendering/Camera/Controller/FPSController.h"

namespace Pixl {

    FPSController::FPSController(Pixl::ICamera *cam) : camera(cam) {}

    bool FPSController::onMouseMoved(Pixl::MouseMovedEvent e) {
        if (firstMouse) {
            lastMousePos = {e.getX(), e.getY()};
            firstMouse = false;
            return true;
        }

        float dx = (e.getX() - lastMousePos.x) * sensitivity;
        float dy = (e.getY() - lastMousePos.y) * sensitivity;
        lastMousePos = {e.getX(), e.getY()};

        // Obtenir l'orientation actuelle
        glm::quat currentOrientation = camera->getOrientation();

        // Yaw: rotation autour de l'axe Y mondial (0,1,0)
        glm::quat yawRotation = glm::angleAxis(glm::radians(-dx), glm::vec3(0, 1, 0));

        // Pitch: rotation autour de l'axe X local (right vector)
        glm::vec3 right = camera->getRightNormal();
        glm::quat pitchRotation = glm::angleAxis(glm::radians(-dy), right);

        // Combiner les rotations dans le bon ordre
        glm::quat newOrientation = yawRotation * currentOrientation * pitchRotation;

        // Limiter le pitch pour éviter le retournement
        glm::vec3 forward = newOrientation * glm::vec3(0, 0, -1);
        const float maxPitch = 89.0f;

        if (forward.y > sin(glm::radians(maxPitch))) {
            // Calculer le pitch actuel
            float pitch = asin(forward.y);
            pitch = glm::clamp(pitch, -glm::radians(maxPitch), glm::radians(maxPitch));

            // Reconstruire l'orientation avec le pitch limité
            forward.y = sin(pitch);
            forward = glm::normalize(forward);

            right = glm::normalize(glm::cross(forward, glm::vec3(0, 1, 0)));
            glm::vec3 up = glm::cross(right, forward);

            glm::mat3 rotationMatrix;
            rotationMatrix[0] = right;
            rotationMatrix[1] = up;
            rotationMatrix[2] = -forward;

            newOrientation = glm::quat_cast(rotationMatrix);
        }

        camera->setOrientation(newOrientation);

        return true;
    }

    void FPSController::resetMouse() {
        firstMouse = true;
    }

    void FPSController::setSensitivity(float sens) {
        sensitivity = sens;
    }

}