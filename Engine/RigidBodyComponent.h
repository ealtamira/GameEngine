#pragma once
#include "Component.h"

class RigidBodyComponent : public Component {
public:
    float velocityX;
    float velocityY;
    float accelerationX;
    float accelerationY;

    RigidBodyComponent(Actor* owner);
    RigidBodyComponent(Actor* owner, float vx, float vy);

    void Update(float deltaTime) override;
    void Read(const rapidjson::Value& value) override;
    std::unique_ptr<Component> Clone(Actor* newOwner) const override;
};