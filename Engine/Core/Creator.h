#pragma once
#include "ICreator.h"

template <typename T>
class Creator : public ICreator {
public:
    Object* Create() override {
        return new T();
    }
};