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

        void updateViewMatrix() const final;

        void updateProjectionMatrix() const final;

        void updateDirection();

    public:
        explicit PerspectiveCamera(float fovY = 70.0f, float aspect = 1.0f, float nearPlane = 0.1f, float farPlane = 1000.0f);

        void setFovY(float fov);

        void setNearFarPlanes(float near, float far);

        void setUp(const glm::vec3& upVector);

        void rotateAt(float newYaw, float newPitch);

        void rotate(float yawOffset, float pitchOffset);

        float getFovY() const;
        float getNearPlane() const;
        float getFarPlane() const;
    };

}

#endif //PIXLENGINE_PERSPECTIVECAMERA_H
