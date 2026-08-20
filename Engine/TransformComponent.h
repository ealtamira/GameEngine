#pragma once
#include "Component.h"

class TransformComponent : public Component {
public:
    float x = 0.0f;
    float y = 0.0f;
    float width = 0.0f;
    float height = 0.0f;

    TransformComponent(Actor* owner, float startX = 0.0f, float startY = 0.0f, float w = 0.0f, float h = 0.0f);

    void Update(float deltaTime) override {}
    std::unique_ptr<Component> Clone(Actor* newOwner) const override;
};