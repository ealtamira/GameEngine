#pragma once

#include <memory>
#include <rapidjson/document.h>
#include "ISerializable.h"

class Actor;

class Component : public ISerializable {
public:
    Actor* owner;

    Component(Actor* owner);
    virtual ~Component() = default;

    virtual void Update(float deltaTime);
    virtual void Draw();

    virtual std::unique_ptr<Component> Clone(Actor* newOwner) const = 0;
    virtual void Read(const rapidjson::Value& value) override = 0;
};