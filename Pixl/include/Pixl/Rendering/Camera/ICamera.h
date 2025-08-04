//
// Created by ChiroYuki on 01/08/2025.
//

#ifndef PIXLENGINE_ICAMERA_H
#define PIXLENGINE_ICAMERA_H

#include <glm/glm.hpp>

namespace Pixl {

    class ICamera {
    public:
        virtual ~ICamera() = default;

        virtual glm::vec3 getPosition() = 0;
        virtual glm::quat getOrientation() = 0;

        virtual void setPosition(const glm::vec3& pos) = 0;
        virtual void setOrientation(const glm::quat& orientation) = 0;
        virtual void setAspectRatio(float aspect) = 0;

        virtual const glm::mat4& getViewMatrix() = 0;
        virtual const glm::mat4& getProjectionMatrix() = 0;
        virtual glm::mat4 getViewProjectionMatrix() = 0;

        virtual const glm::vec3& getPosition() const = 0;
        virtual glm::vec3 getForwardNormal() const = 0;
        virtual glm::vec3 getRightNormal() const = 0;
        virtual glm::vec3 getUpNormal() const = 0;

        virtual void lookAt(const glm::vec3& target, const glm::vec3& up = glm::vec3(0, 1, 0)) = 0;
        virtual void move(const glm::vec3& offset) = 0;
        virtual void moveRelative(const glm::vec3& offset) = 0;
    };

}

#endif //PIXLENGINE_ICAMERA_H
