#pragma once
#include "Component.h"

class RigidBodyComponent : public Component {
public:
    float velocityX;
    float velocityY;
    float accelerationX;
    float accelerationY;

    RigidBodyComponent(Actor* owner, float vx = 0.0f, float vy = 0.0f);

    void Update(float deltaTime) override;
    std::unique_ptr<Component> Clone(Actor* newOwner) const override;
};