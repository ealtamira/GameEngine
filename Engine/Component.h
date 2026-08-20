#pragma once

#include <memory>

class Actor;

class Component {
public:
    Actor* owner;

    Component(Actor* owner);
    virtual ~Component() = default;

    virtual void Update(float deltaTime);
    virtual void Draw();

    virtual std::unique_ptr<Component> Clone(Actor* newOwner) const = 0;
};