#include "pch.h"
#include "Player.h"
#include "Creator.h"
#include "Factory.h"

static RegisterHelper regPlayer("Player", std::make_unique<Creator<Player>>());