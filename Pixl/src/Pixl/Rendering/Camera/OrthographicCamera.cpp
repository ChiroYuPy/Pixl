//
// Created by ChiroYuki on 02/08/2025.
//

#include "Pixl/Rendering/Camera/OrthographicCamera.h"

namespace Pixl {

    OrthographicCamera::OrthographicCamera(float aspect, float zoom)
            : aspectRatio(aspect), zoom(zoom) {
        updateProjectionMatrix();
        updateViewMatrix();
    }

    void OrthographicCamera::setAspectRatio(float aspect) {
        if (aspect != aspectRatio) {
            aspectRatio = aspect;
            projDirty = true;
        }
    }

    void OrthographicCamera::setPosition(const glm::vec3& pos) {
        if (pos != position) {
            position = pos;
            viewDirty = true;
        }
    }

    void OrthographicCamera::setDirection(const glm::vec3& dir) {
        if (dir != direction) {
            direction = glm::normalize(dir);
            viewDirty = true;
        }
    }

    const glm::mat4& OrthographicCamera::getViewMatrix() {
        if (viewDirty)
            updateViewMatrix();
        return viewMatrix;
    }

    const glm::mat4& OrthographicCamera::getProjectionMatrix() {
        if (projDirty)
            updateProjectionMatrix();
        return projectionMatrix;
    }

    const glm::vec3& OrthographicCamera::getPosition() const {
        return position;
    }

    void OrthographicCamera::setZoom(float z) {
        if (z != zoom && z > 0.0f) {
            zoom = z;
            projDirty = true;
        }
    }

    void OrthographicCamera::setRotation(float rot) {
        if (rot != rotation) {
            rotation = rot;
            viewDirty = true;
        }
    }

    void OrthographicCamera::updateViewMatrix() {
        // Pour la 2D, on peut utiliser la rotation autour de l'axe Z
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
                              glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0, 0, 1));

        viewMatrix = glm::inverse(transform);
        viewDirty = false;
    }

    void OrthographicCamera::updateProjectionMatrix() {
        float left = -aspectRatio * zoom;
        float right = aspectRatio * zoom;
        float bottom = -zoom;
        float top = zoom;

        projectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
        projDirty = false;
    }

}