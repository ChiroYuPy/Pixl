//
// Created by ChiroYuki on 05/08/2025.
//

#include "Pixl/Rendering/Camera/Controller/OrbitController.h"

namespace Pixl {

    OrbitController::OrbitController(ICamera* cam) : BaseCameraController(cam) {
        if (camera) {
            // Calculer la configuration initiale basée sur la position actuelle
            glm::vec3 pos = camera->getPosition();
            distance = glm::length(pos - target);

            // Calculer azimuth et elevation
            glm::vec3 dir = glm::normalize(pos - target);
            azimuth = glm::degrees(atan2(dir.x, dir.z));
            elevation = glm::degrees(asin(dir.y));
        }
    }

    void OrbitController::update(Time& deltaTime) {
        if (!enabled || !camera) return;

        updateCameraPosition();
    }

    bool OrbitController::onMouseMoved(const MouseMovedEvent& e) {
        if (!enabled || !camera) return false;

        glm::vec2 delta = getMouseDelta(e);
        if (glm::length(delta) == 0.0f) return false;

        if (isOrbiting) {
            handleOrbit(delta.x, delta.y);
            return true;
        } else if (isPanning) {
            handlePan(delta.x, delta.y);
            return true;
        }

        return false;
    }

    bool OrbitController::onMousePressed(const MouseButtonPressedEvent& e) {
        if (!enabled) return false;

        if (e.getMouseButton() == orbitButton) {
            isOrbiting = true;
            return true;
        } else if (e.getMouseButton() == panButton) {
            isPanning = true;
            return true;
        }

        return false;
    }

    bool OrbitController::onMouseReleased(const MouseButtonReleasedEvent& e) {
        if (!enabled) return false;

        if (e.getMouseButton() == orbitButton) {
            isOrbiting = false;
            return true;
        } else if (e.getMouseButton() == panButton) {
            isPanning = false;
            return true;
        }

        return false;
    }

    bool OrbitController::onMouseScrolled(const MouseScrolledEvent& e) {
        if (!enabled || !camera) return false;

        handleZoom(e.getYOffset());
        return true;
    }

    void OrbitController::setTarget(const glm::vec3& newTarget) {
        target = newTarget;
        updateCameraPosition();
    }

    void OrbitController::setDistance(float newDistance) {
        distance = glm::clamp(newDistance, minDistance, maxDistance);
        updateCameraPosition();
    }

    void OrbitController::setDistanceRange(float minDist, float maxDist) {
        minDistance = minDist;
        maxDistance = maxDist;
        distance = glm::clamp(distance, minDistance, maxDistance);
    }

    void OrbitController::setElevationRange(float minElev, float maxElev) {
        minElevation = minElev;
        maxElevation = maxElev;
        elevation = glm::clamp(elevation, minElevation, maxElevation);
    }

    void OrbitController::updateCameraPosition() {
        // Convertir coordonnées sphériques en cartésiennes
        float azimuthRad = glm::radians(azimuth);
        float elevationRad = glm::radians(elevation);

        glm::vec3 position;
        position.x = target.x + distance * cos(elevationRad) * sin(azimuthRad);
        position.y = target.y + distance * sin(elevationRad);
        position.z = target.z + distance * cos(elevationRad) * cos(azimuthRad);

        camera->setPosition(position);
        camera->lookAt(target);
    }

    void OrbitController::handleOrbit(float dx, float dy) {
        azimuth -= dx;
        elevation += dy;

        // Contraindre l'élévation
        elevation = glm::clamp(elevation, minElevation, maxElevation);

        // Normaliser l'azimuth
        while (azimuth > 180.0f) azimuth -= 360.0f;
        while (azimuth < -180.0f) azimuth += 360.0f;
    }

    void OrbitController::handlePan(float dx, float dy) {
        glm::vec3 right = camera->getRightNormal();
        glm::vec3 up = camera->getUpNormal();

        glm::vec3 panOffset = (-right * dx + up * dy) * panSpeed * distance * 0.001f;
        target += panOffset;
    }

    void OrbitController::handleZoom(float delta) {
        distance -= delta * zoomSpeed;
        distance = glm::clamp(distance, minDistance, maxDistance);
    }

    void OrbitController::reset() {
        BaseCameraController::reset();
        isOrbiting = false;
        isPanning = false;
        target = glm::vec3(0.0f);
        distance = 10.0f;
        azimuth = 0.0f;
        elevation = 0.0f;
    }

}