#pragma once
#include "Actor.h"
#include <iostream>

class Player : public Actor {
public:
    Player() { std::cout << "Player instance constructed." << std::endl; }

    void Initialize() override { std::cout << "Player initialized." << std::endl; }
    float GetRadius() override { return 15.5f; }
};