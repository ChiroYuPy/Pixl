//
// Created by ChiroYuki on 11/08/2025.
//

#ifndef PIXLENGINE_MESHCOMPONENT_H
#define PIXLENGINE_MESHCOMPONENT_H

#include "Pixl/Rendering/Geometry/Geometry.h"
#include "Pixl/Rendering/Material/Material.h"

namespace Pixl {

    struct MeshComponent {
        Ref<Geometry> geometry;
        Ref<Material> material;
        bool visible = true;
    };

}

#endif //PIXLENGINE_MESHCOMPONENT_H
