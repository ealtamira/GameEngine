#pragma once
class Object;

class ICreator {
public:
    virtual ~ICreator() = default;
    virtual Object* Create() = 0;
};