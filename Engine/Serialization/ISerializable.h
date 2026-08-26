#pragma once
#include <rapidjson/document.h>

class ISerializable
{
public:
    virtual ~ISerializable() = default;
    virtual void Read(const rapidjson::Value& value) = 0;
};