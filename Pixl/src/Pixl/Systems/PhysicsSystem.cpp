//
// Created by ChiroYuki on 15/08/2025.
//

#include "Pixl/Systems/PhysicsSystem.h"
#include <glm/glm.hpp>

namespace Pixl {

    constexpr glm::vec3 GRAVITY = {0.0f, -9.81f, 0.0f};

    void PhysicsSystem::applyGravity(RigidBodyComponent& rigidBody) {
        rigidBody.acceleration += GRAVITY;
    }

    void PhysicsSystem::integrate(RigidBodyComponent& rigidBody, TransformComponent& transform, Time deltaTime) {
        float dt = deltaTime.asSeconds();
        glm::vec3 oldPosition = transform.position;

        rigidBody.velocity += rigidBody.acceleration * dt;
        transform.position += rigidBody.velocity * dt;
        rigidBody.acceleration = glm::vec3(0.0f);

        if (transform.position != oldPosition) {
            transform.isDirty = true;
        }
    }

    void PhysicsSystem::handleGroundCollision(RigidBodyComponent& rigidBody, TransformComponent& transform, const ColliderComponent& collider) {
        // Le sol est à y = 0, donc l'objet touche le sol quand position.y - radius <= 0
        if (transform.position.y - collider.radius <= 0.0f) {
            transform.position.y = collider.radius; // Placer l'objet juste au-dessus du sol
            rigidBody.velocity.y = 0.0f;
            transform.isDirty = true;
        }
    }

    bool PhysicsSystem::checkSphereCollision(const TransformComponent& aTrans, const ColliderComponent& aCol,
                                             const TransformComponent& bTrans, const ColliderComponent& bCol) {
        // Distance entre les centres des deux sphères
        glm::vec3 distance = bTrans.position - aTrans.position;
        float distanceLength = glm::length(distance);

        // Somme des rayons
        float radiusSum = aCol.radius + bCol.radius;

        // Collision si la distance est inférieure à la somme des rayons
        return distanceLength <= radiusSum;
    }

    void PhysicsSystem::resolveCollision(RigidBodyComponent& rigidBodyA, TransformComponent& transformA, const ColliderComponent& colliderA,
                                         RigidBodyComponent& rigidBodyB, TransformComponent& transformB, const ColliderComponent& colliderB) {
        // Vecteur de collision (de A vers B)
        glm::vec3 collisionVector = transformB.position - transformA.position;
        float distance = glm::length(collisionVector);

        if (distance == 0.0f) return; // Éviter division par zéro

        // Normaliser le vecteur de collision
        glm::vec3 collisionNormal = collisionVector / distance;

        // Calculer l'overlap (chevauchement)
        float overlap = (colliderA.radius + colliderB.radius) - distance;

        // Séparer les objets (chacun bouge de la moitié de l'overlap)
        glm::vec3 separation = collisionNormal * (overlap * 0.5f);
        transformA.position -= separation;
        transformB.position += separation;

        // Résolution simple des vitesses : arrêter le mouvement dans la direction de collision
        // Projeter les vitesses sur la normale de collision
        float velA = glm::dot(rigidBodyA.velocity, collisionNormal);
        float velB = glm::dot(rigidBodyB.velocity, collisionNormal);

        // Si les objets se rapprochent, inverser leurs vitesses dans cette direction
        if (velA > velB) {
            rigidBodyA.velocity -= collisionNormal * velA;
            rigidBodyB.velocity -= collisionNormal * velB;
        }

        transformA.isDirty = true;
        transformB.isDirty = true;
    }

    void PhysicsSystem::update(Scene& scene, Time deltaTime) {
        auto& registry = scene.getRegistry();
        auto view = registry.view<TransformComponent, RigidBodyComponent, ColliderComponent>();

        // 1. Appliquer gravité et intégrer les positions
        for (auto entity : view) {
            auto& transform = view.get<TransformComponent>(entity);
            auto& rigidBody = view.get<RigidBodyComponent>(entity);
            auto& collider = view.get<ColliderComponent>(entity);

            applyGravity(rigidBody);
            integrate(rigidBody, transform, deltaTime);
            handleGroundCollision(rigidBody, transform, collider);
        }

        // 2. Vérifier collisions entre objets (collision sphérique)
        for (auto itA = view.begin(); itA != view.end(); ++itA) {
            auto entityA = *itA;
            auto& transA = view.get<TransformComponent>(entityA);
            auto& colA = view.get<ColliderComponent>(entityA);
            auto& rbA = view.get<RigidBodyComponent>(entityA);

            auto itB = itA;
            ++itB;
            for (; itB != view.end(); ++itB) {
                auto entityB = *itB;
                auto& transB = view.get<TransformComponent>(entityB);
                auto& colB = view.get<ColliderComponent>(entityB);
                auto& rbB = view.get<RigidBodyComponent>(entityB);

                if (checkSphereCollision(transA, colA, transB, colB)) {
                    resolveCollision(rbA, transA, colA, rbB, transB, colB);
                }
            }
        }
    }

}