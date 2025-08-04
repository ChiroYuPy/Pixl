//
// Created by ChiroYuki on 04/08/2025.
//

#include "Pixl/Rendering/Camera/BaseCamera.h"

namespace Pixl {

    void BaseCamera::setPosition(const glm::vec3& pos) {
        if (pos != position) {
            position = pos;
            viewDirty = true;
        }
    }

    void BaseCamera::setOrientation(const glm::quat& orientation) {
        glm::quat normalized = glm::normalize(orientation);
        if (normalized != this->orientation) {
            this->orientation = normalized;
            viewDirty = true;
        }
    }

    void BaseCamera::setAspectRatio(float aspect) {
        if (aspect != aspectRatio) {
            aspectRatio = aspect;
            projDirty = true;
        }
    }

    const glm::mat4& BaseCamera::getViewMatrix() {
        if (viewDirty) {
            updateViewMatrix();
            viewDirty = false;
        }
        return viewMatrix;
    }

    const glm::mat4& BaseCamera::getProjectionMatrix() {
        if (projDirty) {
            updateProjectionMatrix();
            projDirty = false;
        }
        return projectionMatrix;
    }

    glm::vec3 BaseCamera::getPosition() {
        return position;
    }

    glm::quat BaseCamera::getOrientation() {
        return orientation;
    }

    glm::mat4 BaseCamera::getViewProjectionMatrix() {
        return getProjectionMatrix() * getViewMatrix();
    }

    const glm::vec3& BaseCamera::getPosition() const {
        return position;
    }

    glm::vec3 BaseCamera::getForwardNormal() const {
        return orientation * glm::vec3(0, 0, -1);
    }

    glm::vec3 BaseCamera::getRightNormal() const {
        return orientation * glm::vec3(1, 0, 0);
    }

    glm::vec3 BaseCamera::getUpNormal() const {
        return orientation * glm::vec3(0, 1, 0);
    }

    void BaseCamera::lookAt(const glm::vec3& target, const glm::vec3& up) {
        glm::vec3 forward = glm::normalize(target - position);
        setDirection(forward, up);
    }

    void BaseCamera::move(const glm::vec3& offset) {
        position += offset;
        viewDirty = true;
    }

    void BaseCamera::moveRelative(const glm::vec3& offset) {
        position += orientation * offset;
        viewDirty = true;
    }

    void BaseCamera::rotate(const glm::quat& rotation) {
        orientation = glm::normalize(rotation * orientation);
        viewDirty = true;
    }

    void BaseCamera::rotate(const glm::vec3& axis, float angle) {
        rotate(glm::angleAxis(angle, axis));
    }

    void BaseCamera::setDirection(const glm::vec3& forward, const glm::vec3& worldUp) {
        glm::vec3 forwardNorm = glm::normalize(forward);
        glm::vec3 right = glm::normalize(glm::cross(forwardNorm, worldUp));
        glm::vec3 up = glm::cross(right, forwardNorm);

        glm::mat3 rotationMatrix(right, up, -forwardNorm);
        orientation = glm::quat_cast(rotationMatrix);
        viewDirty = true;
    }

}