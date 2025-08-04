//
// Created by ChiroYuki on 04/08/2025.
//

#ifndef PIXLENGINE_FPSCONTROLLER_H
#define PIXLENGINE_FPSCONTROLLER_H

#include "Pixl/Rendering/Camera/ICamera.h"
#include "Pixl/Events/MouseEvent.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Pixl {

    class FPSController {
    private:
        Pixl::ICamera *camera;
        float sensitivity = 0.125f;
        glm::vec2 lastMousePos;
        bool firstMouse = true;

    public:
        FPSController(Pixl::ICamera *cam);

        bool onMouseMoved(Pixl::MouseMovedEvent e);

        void resetMouse();

        void setSensitivity(float sens);
    };

}

#endif //PIXLENGINE_FPSCONTROLLER_H
