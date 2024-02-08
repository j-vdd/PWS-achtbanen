#pragma once

#include "ecs/Registry.h"
#include "graphics/Mesh.h"

class PlayerSystem
{
public:
	static void update(Registry& registry, float dt);
};