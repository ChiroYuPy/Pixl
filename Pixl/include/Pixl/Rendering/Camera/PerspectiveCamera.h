//
// Created by ChiroYuki on 01/08/2025.
//

#ifndef PIXLENGINE_PERSPECTIVECAMERA_H
#define PIXLENGINE_PERSPECTIVECAMERA_H

#include "ICamera.h"
#include "BaseCamera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Pixl {

    class PerspectiveCamera : public BaseCamera {
    private:
        float fovY{70.0f};
        float nearPlane{0.1f};
        float farPlane{1000.0f};
        float yaw = 0.0f;
        float pitch = 0.0f;

        void updateViewMatrix() const final {
            viewMatrix = glm::lookAt(position, position + direction, up);
            viewDirty = false;
        }

        void updateProjectionMatrix() const final {
            projectionMatrix = glm::perspective(glm::radians(fovY), aspectRatio, nearPlane, farPlane);
            projDirty = false;
        }

        void updateDirection() {
            float yawRad = glm::radians(yaw);
            float pitchRad = glm::radians(pitch);

            direction.x = std::cos(pitchRad) * std::cos(yawRad);
            direction.y = std::sin(pitchRad);
            direction.z = std::cos(pitchRad) * std::sin(yawRad);
            direction = glm::normalize(direction);

            viewDirty = true;
        }

    public:
        explicit PerspectiveCamera(float fovY = 70.0f, float aspect = 1.0f,
                                   float nearPlane = 0.1f, float farPlane = 1000.0f)
                : fovY(fovY), nearPlane(nearPlane), farPlane(farPlane) {
            aspectRatio = aspect;
            updateProjectionMatrix();
            updateViewMatrix();
        }

        // Setters spécifiques à la caméra perspective
        void setFovY(float fov) {
            if (fov != fovY) {
                fovY = fov;
                projDirty = true;
            }
        }

        void setNearFarPlanes(float near, float far) {
            if (near != nearPlane || far != farPlane) {
                nearPlane = near;
                farPlane = far;
                projDirty = true;
            }
        }

        void setUp(const glm::vec3& upVector) {
            glm::vec3 normalizedUp = glm::normalize(upVector);
            if (normalizedUp != up) {
                up = normalizedUp;
                viewDirty = true;
            }
        }

        void rotateAt(float newYaw, float newPitch) {
            yaw = newYaw;
            pitch = newPitch;
            updateDirection();
        }

        void rotate(float yawOffset, float pitchOffset) {
            yaw += yawOffset;
            pitch += pitchOffset;
            updateDirection();
        }

        float getFovY() const { return fovY; }
        float getNearPlane() const { return nearPlane; }
        float getFarPlane() const { return farPlane; }
    };

}

#endif //PIXLENGINE_PERSPECTIVECAMERA_H
