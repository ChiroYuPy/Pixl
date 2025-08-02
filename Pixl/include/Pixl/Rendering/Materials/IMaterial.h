//
// Created by ChiroYuki on 02/08/2025.
//

#ifndef PIXLENGINE_IMATERIAL_H
#define PIXLENGINE_IMATERIAL_H

namespace Pixl {

    class IMaterial {
    public:
        virtual void bind() const = 0;

        virtual ~IMaterial() = default;
    };

}

#endif //PIXLENGINE_IMATERIAL_H
