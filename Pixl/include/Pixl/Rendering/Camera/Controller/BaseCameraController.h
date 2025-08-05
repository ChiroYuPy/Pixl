//
// Created by ChiroYuki on 05/08/2025.
//

#ifndef PIXLENGINE_BASECAMERACONTROLLER_H
#define PIXLENGINE_BASECAMERACONTROLLER_H

#include <unordered_map>
#include "ICameraController.h"

namespace Pixl {

    class BaseCameraController : public ICameraController {
    protected:
        // État du contrôleur
        glm::vec2 lastMousePos{0.0f};
        bool firstMouse = true;

        // Configuration générale
        float mouseSensitivity = 0.125f;
        float movementSpeed = 8.0f;
        bool invertY = false;

        // État des touches
        std::unordered_map<int, bool> keyStates;

        // Helpers communs
        glm::vec2 getMouseDelta(const MouseMovedEvent& e);
        bool isKeyPressed(int keyCode) const;
        void updateKeyState(int keyCode, bool pressed);

    public:
        BaseCameraController(ICamera* cam) : ICameraController(cam) {}

        // Configuration
        void setMouseSensitivity(float sensitivity) { mouseSensitivity = sensitivity; }
        void setMovementSpeed(float speed) { movementSpeed = speed; }
        void setInvertY(bool invert) { invertY = invert; }

        float getMouseSensitivity() const { return mouseSensitivity; }
        float getMovementSpeed() const { return movementSpeed; }
        bool getInvertY() const { return invertY; }

        void reset() override;
    };

}

#endif //PIXLENGINE_BASECAMERACONTROLLER_H
