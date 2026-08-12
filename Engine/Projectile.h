#pragma once
#include "Actor.h"
#include <iostream>

class Projectile : public Actor {
public:
    Projectile() { std::cout << "Projectile instance constructed." << std::endl; }
    void Initialize() override { std::cout << "Projectile initialized." << std::endl; }
};