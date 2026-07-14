#pragma once
#include "Vector3.h"

namespace nu
{
    struct Transform
    {
        Vector3 position;
        Vector3 rotation;
        Vector3 scale;

        Transform();
    };
}