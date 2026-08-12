#include "pch.h"
#include "Enemy.h"
#include "Creator.h"
#include "Factory.h"

static RegisterHelper regEnemy("Enemy", std::make_unique<Creator<Enemy>>());