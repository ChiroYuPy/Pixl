//
// Created by ChiroYuki on 01/08/2025.
//

#include "Pixl/Graphics/Rendering/Camera/PerspectiveCamera.h"

namespace Pixl {

    PerspectiveCamera::PerspectiveCamera(float fovY, float aspect, float nearPlane, float farPlane)
            : fovY(fovY), aspectRatio(aspect), nearPlane(nearPlane), farPlane(farPlane),
              position(0.0f), direction(0.0f, 0.0f, -1.0f) {
        updateProjectionMatrix();
        updateViewMatrix();
    }

    void PerspectiveCamera::setAspectRatio(float aspect) {
        if (aspect != aspectRatio) {
            aspectRatio = aspect;
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
        if (dir != direction) {
            direction = glm::normalize(dir);
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

    const glm::vec3& PerspectiveCamera::getPosition() const {
        return position;
    }

    void PerspectiveCamera::updateViewMatrix() {
        viewMatrix = glm::lookAt(position, position + direction, up);
        viewDirty = false;
    }

    void PerspectiveCamera::updateProjectionMatrix() {
        projectionMatrix = glm::perspective(glm::radians(fovY), aspectRatio, nearPlane, farPlane);
        projDirty = false;
    }

}