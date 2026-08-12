#pragma once
#include "Object.h"

class Actor : public Object {
public:
    bool IsActor = true;
    virtual float GetRadius() { return 10.0f; }

    virtual ~Actor() = default;
};