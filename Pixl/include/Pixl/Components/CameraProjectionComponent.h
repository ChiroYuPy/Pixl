//
// Created by ChiroYuki on 11/08/2025.
//

#ifndef PIXLENGINE_CAMERAPROJECTIONCOMPONENT_H
#define PIXLENGINE_CAMERAPROJECTIONCOMPONENT_H

namespace Pixl {

    struct CameraProjection {
        float fov = 45.f;
        float nearPlane = 0.1f;
        float farPlane = 1000.f;
        float aspectRatio = 1.f;
    };

}

#endif //PIXLENGINE_CAMERAPROJECTIONCOMPONENT_H
