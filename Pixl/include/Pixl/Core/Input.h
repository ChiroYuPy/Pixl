//
// Created by ChiroYuki on 26/07/2025.
//

#ifndef PIXLENGINE_INPUT_H
#define PIXLENGINE_INPUT_H

#include "Pixl/Core/KeyCodes.h"
#include "Pixl/Core/MouseCodes.h"

#include <glm/glm.hpp>

namespace Pixl {

    class Input
    {
    public:
        static bool isKeyPressed(KeyCode key);

        static bool isMouseButtonPressed(MouseCode button);
        static glm::vec2 getMousePosition();
    };

}

#endif //PIXLENGINE_INPUT_H
