//
// Created by ChiroYuki on 05/08/2025.
//

#ifndef PIXLENGINE_ORBITCONTROLLER_H
#define PIXLENGINE_ORBITCONTROLLER_H

#include "BaseCameraController.h"

namespace Pixl {

    class OrbitController : public BaseCameraController {
    private:
        glm::vec3 target{0.0f};
        float distance = 10.0f;
        float minDistance = 1.0f;
        float maxDistance = 100.0f;

        float azimuth = 0.0f;    // rotation horizontale
        float elevation = 0.0f;  // rotation verticale
        float minElevation = -89.999f;
        float maxElevation = 89.999f;

        // État de l'interaction
        bool isOrbiting = false;
        bool isPanning = false;
        int orbitButton = 0;     // bouton pour orbiter (0 = gauche)
        int panButton = 2;       // bouton pour pan (2 = droite)

        float zoomSpeed = 2.0f;
        float panSpeed = 1.0f;

    public:
        OrbitController(ICamera* cam);

        void update(Time& deltaTime) override;
        bool onMouseMoved(const MouseMovedEvent& e) override;
        bool onMousePressed(const MouseButtonPressedEvent& e) override;
        bool onMouseReleased(const MouseButtonReleasedEvent& e) override;
        bool onMouseScrolled(const MouseScrolledEvent& e) override;

        // Configuration
        void setTarget(const glm::vec3& target);
        void setDistance(float distance);
        void setDistanceRange(float minDist, float maxDist);
        void setElevationRange(float minElev, float maxElev);
        void setZoomSpeed(float speed) { zoomSpeed = speed; }
        void setPanSpeed(float speed) { panSpeed = speed; }

        void setOrientation(float a, float e);

        const glm::vec3& getTarget() const { return target; }
        float getDistance() const { return distance; }

        void reset() override;

    private:
        void updateCameraPosition();
        void handleOrbit(float dx, float dy);
        void handlePan(float dx, float dy);
        void handleZoom(float delta);
    };

}

#endif //PIXLENGINE_ORBITCONTROLLER_H
