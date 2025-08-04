//
// Created by ChiroYuki on 04/08/2025.
//

#ifndef PIXLENGINE_BASECAMERA_H
#define PIXLENGINE_BASECAMERA_H

#include "ICamera.h"
#include <glm/gtc/quaternion.hpp>

namespace Pixl {

    class BaseCamera : public ICamera {
    protected:
        glm::vec3 position{0.0f, 0.0f, 0.0f};
        glm::quat orientation{1.0f, 0.0f, 0.0f, 0.0f};
        glm::vec3 worldUp{0.0f, 1.0f, 0.0f};
        float aspectRatio{1.0f};

        mutable glm::mat4 viewMatrix{1.0f};
        mutable glm::mat4 projectionMatrix{1.0f};
        mutable bool viewDirty{true};
        mutable bool projDirty{true};

        virtual void updateViewMatrix() const = 0;
        virtual void updateProjectionMatrix() const = 0;

    public:
        BaseCamera() = default;
        virtual ~BaseCamera() = default;

        // Setters
        void setPosition(const glm::vec3& pos) override;
        void setOrientation(const glm::quat& orientation) override;
        void setAspectRatio(float aspect) override;

        // Getters
        glm::vec3 getPosition() override;
        glm::quat getOrientation() override;

        const glm::mat4& getViewMatrix() override;
        const glm::mat4& getProjectionMatrix() override;
        glm::mat4 getViewProjectionMatrix() override;

        const glm::vec3& getPosition() const override;
        glm::vec3 getForwardNormal() const override;
        glm::vec3 getRightNormal() const override;
        glm::vec3 getUpNormal() const override;

        // Utilitaires
        void lookAt(const glm::vec3& target, const glm::vec3& up = glm::vec3(0, 1, 0)) override;
        void move(const glm::vec3& offset) override;
        void moveRelative(const glm::vec3& offset) override;

        // Orientation helpers
        void rotate(const glm::quat& rotation);
        void rotate(const glm::vec3& axis, float angle);
        void setDirection(const glm::vec3& forward, const glm::vec3& worldUp = glm::vec3(0, 1, 0));
    };

}

#endif //PIXLENGINE_BASECAMERA_H
