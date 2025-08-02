//
// Created by ChiroYuki on 02/08/2025.
//

#ifndef PIXLENGINE_ORTHOGRAPHICCAMERA_H
#define PIXLENGINE_ORTHOGRAPHICCAMERA_H

#include "ICamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Pixl {

    class OrthographicCamera : public ICamera {
    private:
        glm::mat4 projectionMatrix;
        glm::mat4 viewMatrix;

        glm::vec3 position = {0.0f, 0.0f, 0.0f};
        glm::vec3 direction = {0.0f, 0.0f, -1.0f};
        glm::vec3 up = {0.0f, 1.0f, 0.0f};

        float rotation = 0.0f;
        float aspectRatio = 1.0f;
        float zoom = 1.0f;

        bool viewDirty = true;
        bool projDirty = true;

        void updateViewMatrix();
        void updateProjectionMatrix();

    public:
        OrthographicCamera(float aspect, float zoom = 1.0f);

        // Interface ICamera
        void setAspectRatio(float aspect) override;
        void setPosition(const glm::vec3& pos) override;
        void setDirection(const glm::vec3& dir) override;
        const glm::mat4& getViewMatrix() override;
        const glm::mat4& getProjectionMatrix() override;
        const glm::vec3& getPosition() const override;

        // Méthodes spécifiques à la caméra orthographique
        void setZoom(float z);
        float getZoom() const { return zoom; }

        void setRotation(float rot);
        float getRotation() const { return rotation; }
    };

}

#endif //PIXLENGINE_ORTHOGRAPHICCAMERA_H
