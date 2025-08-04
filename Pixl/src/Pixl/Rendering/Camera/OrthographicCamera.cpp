//
// Created by ChiroYuki on 02/08/2025.
//

#include "Pixl/Rendering/Camera/OrthographicCamera.h"

namespace Pixl {


    void OrthographicCamera::updateViewMatrix() const {
        const glm::mat4 identity(1.0f);
        const glm::mat4 translation = glm::translate(identity, position);
        const glm::mat4 rotationMat = glm::rotate(identity, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
        const glm::mat4 transform = translation * rotationMat;

        viewMatrix = glm::inverse(transform);
        viewDirty = false;
    }

    void OrthographicCamera::updateProjectionMatrix() const {
        float actualLeft = left * zoom;
        float actualRight = right * zoom;
        float actualBottom = bottom * zoom;
        float actualTop = top * zoom;

        projectionMatrix = glm::ortho(actualLeft, actualRight, actualBottom, actualTop, nearPlane, farPlane);
        projDirty = false;
    }

    void OrthographicCamera::updateBounds() {
        left = -aspectRatio * zoom;
        right = aspectRatio * zoom;
        bottom = -zoom;
        top = zoom;
    }

    OrthographicCamera::OrthographicCamera(float aspect, float zoom)
    : zoom(zoom) {
        aspectRatio = aspect;
        updateBounds();
        updateProjectionMatrix();
        updateViewMatrix();
    }

    OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float nearPlane, float farPlane)
    : left(left), right(right), bottom(bottom), top(top), nearPlane(nearPlane), farPlane(farPlane) {
        zoom = 1.0f;
        aspectRatio = (right - left) / (top - bottom);
        updateProjectionMatrix();
        updateViewMatrix();
    }

    void OrthographicCamera::setAspectRatio(float aspect) {
        if (aspect != aspectRatio) {
            aspectRatio = aspect;
            updateBounds();
            projDirty = true;
        }
    }

    void OrthographicCamera::setZoom(float z) {
        if (z != zoom && z > 0.0f) {
            zoom = z;
            updateBounds();
            projDirty = true;
        }
    }

    void OrthographicCamera::setRotation(float rot) {
        if (rot != rotation) {
            rotation = rot;
            viewDirty = true;
        }
    }

    void OrthographicCamera::setBounds(float l, float r, float b, float t) {
        this->left = l;
        this->right = r;
        this->bottom = b;
        this->top = t;
        projDirty = true;
    }

    void OrthographicCamera::setNearFarPlanes(float near, float far) {
        if (near != nearPlane || far != farPlane) {
            nearPlane = near;
            farPlane = far;
            projDirty = true;
        }
    }

    float OrthographicCamera::getZoom() const {
        return zoom;
    }

    float OrthographicCamera::getRotation() const {
        return rotation;
    }

    float OrthographicCamera::getLeft() const {
        return left;
    }

    float OrthographicCamera::getRight() const {
        return right;
    }

    float OrthographicCamera::getBottom() const {
        return bottom;
    }

    float OrthographicCamera::getTop() const {
        return top;
    }

    float OrthographicCamera::getNearPlane() const {
        return nearPlane;
    }

    float OrthographicCamera::getFarPlane() const {
        return farPlane;
    }
}