#pragma once

#include "ecs/Registry.h"

#include "Track.h"

namespace RollercoasterSystem
{
	void update(const Track& track, Registry& registry, float dt);
	//void update(const Track& track, Registry& registry, float dt);
}