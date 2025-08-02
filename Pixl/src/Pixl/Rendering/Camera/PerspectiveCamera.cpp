//
// Created by ChiroYuki on 01/08/2025.
//

#include <cmath>

#include "Pixl/Rendering/Camera/PerspectiveCamera.h"

namespace Pixl {

    PerspectiveCamera::PerspectiveCamera(float fovY, float aspect, float nearPlane, float farPlane)
            : fovY(fovY), aspectRatio(aspect), nearPlane(nearPlane), farPlane(farPlane),
              position(0.0f), direction(0.0f, 0.0f, -1.0f), up(0.0f, 1.0f, 0.0f),
              viewDirty(true), projDirty(true) {
        updateProjectionMatrix();
        updateViewMatrix();
    }

    void PerspectiveCamera::setFovY(float fov) {
        if (fov != fovY) {
            fovY = fov;
            projDirty = true;
        }
    }

    void PerspectiveCamera::setAspectRatio(float aspect) {
        if (aspect != aspectRatio) {
            aspectRatio = aspect;
            projDirty = true;
        }
    }

    void PerspectiveCamera::setNearFarPlanes(float near, float far) {
        if (near != nearPlane || far != farPlane) {
            nearPlane = near;
            farPlane = far;
            projDirty = true;
        }
    }

    void PerspectiveCamera::setPosition(const glm::vec3 &pos) {
        if (pos != position) {
            position = pos;
            viewDirty = true;
        }
    }

    void PerspectiveCamera::setDirection(const glm::vec3 &dir) {
        glm::vec3 normalizedDir = glm::normalize(dir);
        if (normalizedDir != direction) {
            direction = normalizedDir;
            viewDirty = true;
        }
    }

    void PerspectiveCamera::setUp(const glm::vec3 &upVector) {
        glm::vec3 normalizedUp = glm::normalize(upVector);
        if (normalizedUp != up) {
            up = normalizedUp;
            viewDirty = true;
        }
    }

    const glm::mat4& PerspectiveCamera::getViewMatrix() {
        if (viewDirty)
            updateViewMatrix();
        return viewMatrix;
    }

    const glm::mat4& PerspectiveCamera::getProjectionMatrix() {
        if (projDirty)
            updateProjectionMatrix();
        return projectionMatrix;
    }

    glm::mat4 PerspectiveCamera::getViewProjectionMatrix() {
        return getProjectionMatrix() * getViewMatrix();
    }

    const glm::vec3& PerspectiveCamera::getPosition() const {
        return position;
    }

    const glm::vec3& PerspectiveCamera::getDirection() const {
        return direction;
    }

    const glm::vec3& PerspectiveCamera::getUp() const {
        return up;
    }

    float PerspectiveCamera::getFovY() const {
        return fovY;
    }

    float PerspectiveCamera::getAspectRatio() const {
        return aspectRatio;
    }

    float PerspectiveCamera::getNearPlane() const {
        return nearPlane;
    }

    float PerspectiveCamera::getFarPlane() const {
        return farPlane;
    }

    void PerspectiveCamera::updateViewMatrix() {
        viewMatrix = glm::lookAt(position, position + direction, up);
        viewDirty = false;
    }

    void PerspectiveCamera::updateProjectionMatrix() {
        projectionMatrix = glm::perspective(glm::radians(fovY), aspectRatio, nearPlane, farPlane);
        projDirty = false;
    }

    void PerspectiveCamera::lookAt(const glm::vec3& target) {
        glm::vec3 newDirection = glm::normalize(target - position);
        if (newDirection != direction) {
            direction = newDirection;
            viewDirty = true;
        }
    }

    void PerspectiveCamera::move(const glm::vec3& offset) {
        position += offset;
        viewDirty = true;
    }

    void PerspectiveCamera::rotate(float yaw, float pitch) {
        // Conversion des angles en radians
        float yawRad = glm::radians(yaw);
        float pitchRad = glm::radians(pitch);

        // Calcul de la nouvelle direction
        direction.x = static_cast<float>(std::cos(pitchRad)) * static_cast<float>(std::cos(yawRad));
        direction.y = static_cast<float>(std::sin(pitchRad));
        direction.z = static_cast<float>(std::cos(pitchRad)) * static_cast<float>(std::sin(yawRad));
        direction = glm::normalize(direction);

        viewDirty = true;
    }

}