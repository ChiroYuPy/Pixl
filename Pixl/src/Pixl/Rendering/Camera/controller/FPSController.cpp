//
// Created by ChiroYuki on 04/08/2025.
//

#include "Pixl/Rendering/Camera/Controller/FPSController.h"

namespace Pixl {

    FPSController::FPSController(ICamera* cam) : BaseCameraController(cam) {
        // Initialiser pitch/yaw basé sur l'orientation actuelle de la caméra
        if (camera) {
            glm::vec3 forward = camera->getForwardNormal();
            yaw = glm::degrees(atan2(forward.x, forward.z));
            pitch = glm::degrees(asin(-forward.y));
        }
    }

    void FPSController::update(Time& deltaTime) {
        if (!enabled || !camera) return;

        updateMovement(deltaTime.asSeconds());
    }

    bool FPSController::onMouseMoved(const MouseMovedEvent& e) {
        if (!enabled || !camera) return false;

        glm::vec2 delta = getMouseDelta(e);
        if (glm::length(delta) > 0.0f) {
            updateRotation(delta.x, delta.y);
            return true;
        }

        return false;
    }

    bool FPSController::onKeyPressed(const KeyPressedEvent& e) {
        if (!enabled) return false;

        updateKeyState(e.getKeyCode(), true);
        return true;
    }

    bool FPSController::onKeyReleased(const KeyReleasedEvent& e) {
        if (!enabled) return false;

        updateKeyState(e.getKeyCode(), false);
        return false;
    }

    void FPSController::updateRotation(float dx, float dy) {
        yaw -= dx;
        pitch -= dy;

        if (constrainPitch) {
            pitch = glm::clamp(pitch, -maxPitch, maxPitch);
        }

        // Construire la rotation finale
        glm::quat qPitch = glm::angleAxis(glm::radians(pitch), glm::vec3(1, 0, 0));
        glm::quat qYaw = glm::angleAxis(glm::radians(yaw), glm::vec3(0, 1, 0));
        glm::quat orientation = qYaw * qPitch;

        camera->setOrientation(orientation);
    }

    void FPSController::updateMovement(float deltaTime) {
        glm::vec3 inputDirection = getMovementInput();

        if (smoothMovement) {
            // Mouvement avec accélération et friction
            if (glm::length(inputDirection) > 0.0f) {
                velocity += inputDirection * acceleration * deltaTime;
            }

            // Appliquer la friction
            velocity *= glm::max(0.0f, 1.0f - friction * deltaTime);

            // Déplacer la caméra
            if (glm::length(velocity) > 0.001f) {
                camera->moveRelative(velocity * deltaTime);
            }
        } else {
            // Mouvement direct
            if (glm::length(inputDirection) > 0.0f) {
                camera->moveRelative(inputDirection * movementSpeed * deltaTime);
            }
        }
    }

    glm::vec3 FPSController::getMovementInput() const {
        glm::vec3 input(0.0f);

        if (isKeyPressed(Key::W)) input.z -= 1.0f;
        if (isKeyPressed(Key::S)) input.z += 1.0f;
        if (isKeyPressed(Key::A)) input.x -= 1.0f;
        if (isKeyPressed(Key::D)) input.x += 1.0f;
        if (isKeyPressed(Key::Space)) input.y += 1.0f;
        if (isKeyPressed(Key::LeftShift)) input.y -= 1.0f;

        if (glm::length(input) > 0.0f) {
            input = glm::normalize(input) * movementSpeed;
        }

        return input;
    }

    void FPSController::reset() {
        BaseCameraController::reset();
        velocity = glm::vec3(0.0f);

        if (camera) {
            // Réinitialiser pitch/yaw
            glm::vec3 forward = camera->getForwardNormal();
            yaw = glm::degrees(atan2(forward.x, forward.z));
            pitch = glm::degrees(asin(-forward.y));
        }
    }

}