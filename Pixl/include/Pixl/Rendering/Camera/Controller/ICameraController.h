//
// Created by ChiroYuki on 05/08/2025.
//

#ifndef PIXLENGINE_ICAMERACONTROLLER_H
#define PIXLENGINE_ICAMERACONTROLLER_H

#include "Pixl/Events/MouseEvent.h"
#include "Pixl/Rendering/Camera/ICamera.h"
#include "Pixl/Events/KeyEvent.h"
#include "Pixl/Core/Time/Time.h"

namespace Pixl {

    class ICameraController {
    protected:
        ICamera* camera;
        bool enabled = true;

    public:
        ICameraController(ICamera* cam) : camera(cam) {}
        virtual ~ICameraController() = default;

        // Interface principale
        virtual void update(Time& deltaTime) {}
        virtual bool onMouseMoved(const MouseMovedEvent& e) { return false; }
        virtual bool onMousePressed(const MouseButtonPressedEvent& e) { return false; }
        virtual bool onMouseReleased(const MouseButtonReleasedEvent& e) { return false; }
        virtual bool onMouseScrolled(const MouseScrolledEvent& e) { return false; }
        virtual bool onKeyPressed(const KeyPressedEvent& e) { return false; }
        virtual bool onKeyReleased(const KeyReleasedEvent& e) { return false; }

        // Contrôle de l'état
        void setEnabled(bool enable) { enabled = enable; }
        bool isEnabled() const { return enabled; }

        // Accès à la caméra
        ICamera* getCamera() const { return camera; }
        void setCamera(ICamera* cam) { camera = cam; }

        // Configuration
        virtual void resetMouse() {}
        virtual void reset() {}
        virtual void setConfiguration(const std::string& config) {}
    };

}

#endif //PIXLENGINE_ICAMERACONTROLLER_H
