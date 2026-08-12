#pragma once
#include "Actor.h"
#include <iostream>

class Enemy : public Actor {
public:
    Enemy() { std::cout << "Enemy instance constructed." << std::endl; }
    void Initialize() override { std::cout << "Enemy initialized." << std::endl; }
};