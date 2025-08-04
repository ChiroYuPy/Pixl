//
// Created by ChiroYuki on 02/08/2025.
//

#include "Pixl/Rendering/Camera/OrthographicCamera.h"

namespace Pixl {

    OrthographicCamera::OrthographicCamera(float aspect) {
        aspectRatio = aspect;
        updateProjectionMatrix();
        updateViewMatrix();
    }

    OrthographicCamera::OrthographicCamera(float left, float right, float bottom,
                                           float top, float nearPlane, float farPlane)
            : left(left), right(right), bottom(bottom), top(top),
              nearPlane(nearPlane), farPlane(farPlane) {
        updateProjectionMatrix();
        updateViewMatrix();
    }

    void OrthographicCamera::updateViewMatrix() const {
        glm::mat4 transform = glm::mat4_cast(orientation);
        transform[3] = glm::vec4(position, 1.0f);
        viewMatrix = glm::inverse(transform);
    }

    void OrthographicCamera::updateProjectionMatrix() const {
        projectionMatrix = glm::ortho(left, right, bottom, top, nearPlane, farPlane);
    }

    void OrthographicCamera::setBounds(float l, float r, float b, float t) {
        if (l != left || r != right || b != bottom || t != top) {
            left = l;
            right = r;
            bottom = b;
            top = t;
            projDirty = true;
        }
    }

    void OrthographicCamera::setNearFarPlanes(float near, float far) {
        if (near != nearPlane || far != farPlane) {
            nearPlane = near;
            farPlane = far;
            projDirty = true;
        }
    }

    float OrthographicCamera::getLeft() const { return left; }
    float OrthographicCamera::getRight() const { return right; }
    float OrthographicCamera::getBottom() const { return bottom; }
    float OrthographicCamera::getTop() const { return top; }
    float OrthographicCamera::getNearPlane() const { return nearPlane; }
    float OrthographicCamera::getFarPlane() const { return farPlane; }

}