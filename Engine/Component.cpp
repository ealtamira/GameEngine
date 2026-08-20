#include "pch.h"
#include "Component.h"

Component::Component(Actor* owner) : owner(owner) {}

void Component::Update(float deltaTime) {}

void Component::Draw() {}

void Component::Read(const rapidjson::Value& value) {}