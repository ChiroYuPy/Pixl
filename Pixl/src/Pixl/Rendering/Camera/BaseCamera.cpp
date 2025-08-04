//
// Created by ChiroYuki on 04/08/2025.
//

#include "Pixl/Rendering/Camera/BaseCamera.h"

namespace Pixl {

    void BaseCamera::setPosition(const glm::vec3 &pos) {
        if (pos != position) {
            position = pos;
            viewDirty = true;
        }
    }

    void BaseCamera::setDirection(const glm::vec3 &dir) {
        glm::vec3 normalizedDir = glm::normalize(dir);
        if (normalizedDir != direction) {
            direction = normalizedDir;
            viewDirty = true;
        }
    }

    void BaseCamera::setAspectRatio(float aspect) {
        if (aspect != aspectRatio) {
            aspectRatio = aspect;
            projDirty = true;
        }
    }

    const glm::mat4 &BaseCamera::getViewMatrix() {
        if (viewDirty) updateViewMatrix();
        return viewMatrix;
    }

    const glm::mat4 &BaseCamera::getProjectionMatrix() {
        if (projDirty) updateProjectionMatrix();
        return projectionMatrix;
    }

    glm::mat4 BaseCamera::getViewProjectionMatrix() {
        return getProjectionMatrix() * getViewMatrix();
    }

    const glm::vec3 &BaseCamera::getPosition() const {
        return position;
    }

    const glm::vec3 &BaseCamera::getDirection() const {
        return direction;
    }

    void BaseCamera::lookAt(const glm::vec3 &target) {
        glm::vec3 newDirection = glm::normalize(target - position);
        if (newDirection != direction) {
            direction = newDirection;
            viewDirty = true;
        }
    }

    void BaseCamera::move(const glm::vec3 &offset) {
        position += offset;
        viewDirty = true;
    }

    const glm::vec3 &BaseCamera::getUp() const {
        return up;
    }

    float BaseCamera::getAspectRatio() const {
        return aspectRatio;
    }

}