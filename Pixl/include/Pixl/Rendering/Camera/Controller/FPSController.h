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
        Pixl::ICamera* camera;
        float sensitivity = 0.125f;
        float pitch = 0.0f; // Accumulateur de pitch
        float yaw = 0.0f;   // Accumulateur de yaw

    public:
        FPSController(Pixl::ICamera* cam) : camera(cam) {}

        bool onMouseMoved(Pixl::MouseMovedEvent e);
    };

}

#endif //PIXLENGINE_FPSCONTROLLER_H
