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
        float fovY{45.0f};
        float nearPlane{0.1f};
        float farPlane{100.0f};

        void updateViewMatrix() const override;
        void updateProjectionMatrix() const override;

    public:
        PerspectiveCamera(float fovY = 45.0f, float aspect = 1.0f,
                          float nearPlane = 0.1f, float farPlane = 100.0f);

        // Setters
        void setFovY(float fov);
        void setNearFarPlanes(float near, float far);

        // Getters
        float getFovY() const;
        float getNearPlane() const;
        float getFarPlane() const;
    };

}

#endif //PIXLENGINE_PERSPECTIVECAMERA_H
