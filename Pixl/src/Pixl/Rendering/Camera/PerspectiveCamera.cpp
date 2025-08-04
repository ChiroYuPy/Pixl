//
// Created by ChiroYuki on 01/08/2025.
//

#include "Pixl/Rendering/Camera/PerspectiveCamera.h"

namespace Pixl {

    void PerspectiveCamera::updateViewMatrix() const {
        viewMatrix = glm::lookAt(position, position + direction, up);
        viewDirty = false;
    }

    void PerspectiveCamera::updateProjectionMatrix() const {
        projectionMatrix = glm::perspective(glm::radians(fovY), aspectRatio, nearPlane, farPlane);
        projDirty = false;
    }

    void PerspectiveCamera::updateDirection() {
        float yawRad = glm::radians(yaw);
        float pitchRad = glm::radians(pitch);

        direction.x = std::cos(pitchRad) * std::cos(yawRad);
        direction.y = std::sin(pitchRad);
        direction.z = std::cos(pitchRad) * std::sin(yawRad);
        direction = glm::normalize(direction);

        viewDirty = true;
    }

    PerspectiveCamera::PerspectiveCamera(float fovY, float aspect, float nearPlane, float farPlane)
    : fovY(fovY), nearPlane(nearPlane), farPlane(farPlane) {
        aspectRatio = aspect;
        updateProjectionMatrix();
        updateViewMatrix();
    }

    void PerspectiveCamera::setFovY(float fov) {
        if (fov != fovY) {
            fovY = fov;
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

    void PerspectiveCamera::setUp(const glm::vec3 &upVector) {
        glm::vec3 normalizedUp = glm::normalize(upVector);
        if (normalizedUp != up) {
            up = normalizedUp;
            viewDirty = true;
        }
    }

    void PerspectiveCamera::rotateAt(float newYaw, float newPitch) {
        yaw = newYaw;
        pitch = newPitch;
        updateDirection();
    }

    void PerspectiveCamera::rotate(float yawOffset, float pitchOffset) {
        yaw += yawOffset;
        pitch += pitchOffset;
        updateDirection();
    }

    float PerspectiveCamera::getFovY() const {
        return fovY;
    }

    float PerspectiveCamera::getNearPlane() const {
        return nearPlane;
    }

    float PerspectiveCamera::getFarPlane() const {
        return farPlane;
    }
}