//
// Created by ChiroYuki on 01/08/2025.
//

#include "Pixl/Rendering/Camera/PerspectiveCamera.h"

namespace Pixl {

    PerspectiveCamera::PerspectiveCamera(float fovY, float aspect,
                                         float nearPlane, float farPlane)
            : fovY(fovY), nearPlane(nearPlane), farPlane(farPlane) {
        aspectRatio = aspect;
        updateProjectionMatrix();
        updateViewMatrix();
    }

    void PerspectiveCamera::updateViewMatrix() const {
        glm::vec3 forward = getForwardNormal();
        viewMatrix = glm::lookAt(position, position + forward, BaseCamera::getUpNormal());
    }

    void PerspectiveCamera::updateProjectionMatrix() const {
        projectionMatrix = glm::perspective(glm::radians(fovY), aspectRatio, nearPlane, farPlane);
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

    float PerspectiveCamera::getFovY() const { return fovY; }
    float PerspectiveCamera::getNearPlane() const { return nearPlane; }
    float PerspectiveCamera::getFarPlane() const { return farPlane; }
}