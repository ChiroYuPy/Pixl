//
// Created by ChiroYuki on 04/08/2025.
//

#ifndef PIXLENGINE_FPSCONTROLLER_H
#define PIXLENGINE_FPSCONTROLLER_H

#include "Pixl/Rendering/Camera/ICamera.h"
#include "Pixl/Events/MouseEvent.h"
#include "BaseCameraController.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Pixl {

    class FPSController : public BaseCameraController {
    private:
        float pitch = 0.0f;
        float yaw = 0.0f;
        float maxPitch = 89.0f;

        // État du mouvement
        glm::vec3 velocity{0.0f};
        float acceleration = 20.0f;
        float friction = 10.0f;

        // Configuration FPS
        bool constrainPitch = true;
        bool smoothMovement = true;

    public:
        FPSController(ICamera* cam);

        void update(Time& deltaTime) override;
        bool onMouseMoved(const MouseMovedEvent& e) override;
        bool onKeyPressed(const KeyPressedEvent& e) override;
        bool onKeyReleased(const KeyReleasedEvent& e) override;

        // Configuration spécifique FPS
        void setMaxPitch(float maxPitch) { this->maxPitch = maxPitch; }
        void setConstrainPitch(bool constrain) { constrainPitch = constrain; }
        void setSmoothMovement(bool smooth) { smoothMovement = smooth; }

        float getMaxPitch() const { return maxPitch; }
        bool getConstrainPitch() const { return constrainPitch; }
        bool getSmoothMovement() const { return smoothMovement; }

        void reset() override;

    private:
        void updateRotation(float dx, float dy);
        void updateMovement(float deltaTime);
        glm::vec3 getMovementInput() const;
    };

}

#endif //PIXLENGINE_FPSCONTROLLER_H
