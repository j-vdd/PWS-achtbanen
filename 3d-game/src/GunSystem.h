#pragma once

#include "ecs/Registry.h"

class GunSystem
{
public:
	static void update(Registry& registry, float dt);
};