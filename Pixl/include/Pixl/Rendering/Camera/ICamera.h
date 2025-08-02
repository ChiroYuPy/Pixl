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

        virtual void setAspectRatio(float aspect) = 0;

        virtual void setPosition(const glm::vec3 &pos) = 0;

        virtual void setDirection(const glm::vec3 &dir) = 0;

        virtual const glm::mat4 &getViewMatrix() = 0;

        virtual const glm::mat4 &getProjectionMatrix() = 0;

        virtual const glm::vec3 &getPosition() const = 0;
    };

}

#endif //PIXLENGINE_ICAMERA_H
