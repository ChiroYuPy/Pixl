//
// Created by ChiroYuki on 01/08/2025.
//

#ifndef PIXLENGINE_PERSPECTIVECAMERA_H
#define PIXLENGINE_PERSPECTIVECAMERA_H

#include "ICamera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Pixl {

    class PerspectiveCamera : public ICamera {
    public:
        PerspectiveCamera(float fovY, float aspect, float nearPlane, float farPlane);

        void setAspectRatio(float aspect) override;

        void setPosition(const glm::vec3 &pos) override;

        void setDirection(const glm::vec3 &dir) override;

        const glm::mat4 &getViewMatrix() override;
        const glm::mat4 &getProjectionMatrix() override;

        const glm::vec3 &getPosition() const override;

    private:
        void updateViewMatrix();

        void updateProjectionMatrix();

        float fovY;
        float aspectRatio;
        float nearPlane;
        float farPlane;

        glm::vec3 position;
        glm::vec3 direction;
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

        glm::mat4 viewMatrix;
        glm::mat4 projectionMatrix;

        bool viewDirty = true;
        bool projDirty = true;
    };

}

#endif //PIXLENGINE_PERSPECTIVECAMERA_H
