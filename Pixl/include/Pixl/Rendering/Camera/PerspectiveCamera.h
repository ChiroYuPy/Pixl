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
        explicit PerspectiveCamera(float fovY = 70.0f, float aspect = 1.f,
                          float nearPlane = 0.1f, float farPlane = 1000.0f);

        // Setters pour les paramètres de projection
        void setFovY(float fov);
        void setAspectRatio(float aspect) override;
        void setNearFarPlanes(float near, float far);

        // Setters pour la transformation de vue
        void setPosition(const glm::vec3& pos) override;
        void setDirection(const glm::vec3& dir) override;
        void setUp(const glm::vec3& upVector);

        // Getters pour les matrices
        const glm::mat4& getViewMatrix() override;
        const glm::mat4& getProjectionMatrix() override;
        glm::mat4 getViewProjectionMatrix();

        // Getters pour les paramètres
        const glm::vec3& getPosition() const override;
        const glm::vec3& getDirection() const;
        const glm::vec3& getUp() const;
        float getFovY() const;
        float getAspectRatio() const;
        float getNearPlane() const;
        float getFarPlane() const;

        // Méthodes utilitaires
        void lookAt(const glm::vec3& target);
        void move(const glm::vec3& offset);
        void rotate(float yaw, float pitch);

    private:
        // Paramètres de projection
        float fovY;
        float aspectRatio;
        float nearPlane;
        float farPlane;

        // Paramètres de vue
        glm::vec3 position;
        glm::vec3 direction;
        glm::vec3 up;

        // Matrices
        glm::mat4 viewMatrix;
        glm::mat4 projectionMatrix;

        // Flags de mise à jour
        bool viewDirty;
        bool projDirty;

        // Méthodes privées de mise à jour
        void updateViewMatrix();
        void updateProjectionMatrix();
    };

}

#endif //PIXLENGINE_PERSPECTIVECAMERA_H
