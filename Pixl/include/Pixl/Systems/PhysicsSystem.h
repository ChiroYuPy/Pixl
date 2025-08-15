//
// Created by ChiroYuki on 15/08/2025.
//

#ifndef PIXLENGINE_PHYSICSSYSTEM_H
#define PIXLENGINE_PHYSICSSYSTEM_H

#include "Pixl/Core/ECS/ISystem.h"
#include "Pixl/Components.h"
#include "Pixl/Core/ECS/Scene.h"
#include "Pixl/Core/Time/Time.h"

namespace Pixl {

    class PhysicsSystem : public ISystem {
    public:
        void update(Scene& scene, Time deltaTime) override;

    private:
        void applyGravity(RigidBodyComponent &rigidBody);

        void integrate(RigidBodyComponent &rigidBody, TransformComponent &transform, Time deltaTime);

        void handleGroundCollision(RigidBodyComponent &rigidBody, TransformComponent &transform);

        bool
        checkSphereCollision(const TransformComponent &aTrans, const ColliderComponent &aCol,
                             const TransformComponent &bTrans,
                             const ColliderComponent &bCol);

        void
        resolveCollision(RigidBodyComponent &rigidBody, TransformComponent &transform,
                         const TransformComponent &otherTransform,
                         const ColliderComponent &otherCollider);

        void
        handleGroundCollision(RigidBodyComponent &rigidBody, TransformComponent &transform,
                              const ColliderComponent &collider);

        void
        resolveCollision(RigidBodyComponent &rigidBodyA, TransformComponent &transformA,
                         const ColliderComponent &colliderA,
                         RigidBodyComponent &rigidBodyB, TransformComponent &transformB,
                         const ColliderComponent &colliderB);
    };

}

#endif //PIXLENGINE_PHYSICSSYSTEM_H
