#pragma once
#include <iostream>

class Object {
public:
    virtual ~Object() = default;

    virtual void Initialize() = 0;
};