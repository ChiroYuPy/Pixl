//
// Created by ChiroYuki on 04/08/2025.
//

#ifndef PIXLENGINE_BASECAMERA_H
#define PIXLENGINE_BASECAMERA_H

#include "ICamera.h"

namespace Pixl {

    class BaseCamera : public ICamera {
    protected:
        glm::vec3 position{0.0f, 0.0f, 0.0f};
        glm::vec3 direction{0.0f, 0.0f, -1.0f};
        glm::vec3 up{0.0f, 1.0f, 0.0f};
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

        void setPosition(const glm::vec3& pos) override;

        void setDirection(const glm::vec3& dir) override;

        void setAspectRatio(float aspect) override;

        const glm::mat4& getViewMatrix() override;

        const glm::mat4& getProjectionMatrix() override;

        glm::mat4 getViewProjectionMatrix() override;

        const glm::vec3& getPosition() const override;

        const glm::vec3& getDirection() const override;

        void lookAt(const glm::vec3& target) override;

        void move(const glm::vec3& offset) override;

        const glm::vec3& getUp() const;
        float getAspectRatio() const;
    };

}

#endif //PIXLENGINE_BASECAMERA_H
