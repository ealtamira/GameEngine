#pragma once
#include "Component.h"

class CircleColliderComponent : public Component {
public:
    float radius;
    float offsetX;
    float offsetY;

    CircleColliderComponent(Actor* owner, float radius, float offsetX = 0.0f, float offsetY = 0.0f);

    bool CheckCollision(const CircleColliderComponent* other) const;

    std::unique_ptr<Component> Clone(Actor* newOwner) const override;
};