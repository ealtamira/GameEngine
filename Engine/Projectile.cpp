#include "pch.h"
#include "Projectile.h"
#include "Creator.h"
#include "Factory.h"

static RegisterHelper regProjectile("Projectile", std::make_unique<Creator<Projectile>>());