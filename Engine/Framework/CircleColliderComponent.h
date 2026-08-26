#pragma once
#include "Component.h"

class CircleColliderComponent : public Component {
public:
    float radius;
    float offsetX;
    float offsetY;

    CircleColliderComponent(Actor* owner);

    CircleColliderComponent(Actor* owner, float radius);

    CircleColliderComponent(Actor* owner, float radius, float offsetX, float offsetY);

    bool CheckCollision(const CircleColliderComponent* other) const;

    void Read(const rapidjson::Value& value) override;
    std::unique_ptr<Component> Clone(Actor* newOwner) const override;
};