//
// Created by ChiroYuki on 02/08/2025.
//

#ifndef PIXLENGINE_ORTHOGRAPHICCAMERA_H
#define PIXLENGINE_ORTHOGRAPHICCAMERA_H

#include "ICamera.h"
#include "BaseCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Pixl {

    class OrthographicCamera : public BaseCamera {
    private:
        float zoom{1.0f};
        float rotation{0.0f};
        float left{-1.0f}, right{1.0f}, bottom{-1.0f}, top{1.0f};
        float nearPlane{-1.0f}, farPlane{1.0f};

        void updateViewMatrix() const final;

        void updateProjectionMatrix() const final;

        void updateBounds();

    public:
        explicit OrthographicCamera(float aspect = 1.0f, float zoom = 1.0f);

        OrthographicCamera(float left, float right, float bottom, float top, float nearPlane = -1.0f, float farPlane = 1.0f);

        void setAspectRatio(float aspect) override;

        void setZoom(float z);

        void setRotation(float rot);

        void setBounds(float l, float r, float b, float t);

        void setNearFarPlanes(float near, float far);

        float getZoom() const;
        float getRotation() const;
        float getLeft() const;
        float getRight() const;
        float getBottom() const;
        float getTop() const;
        float getNearPlane() const;
        float getFarPlane() const;
    };

}

#endif //PIXLENGINE_ORTHOGRAPHICCAMERA_H
