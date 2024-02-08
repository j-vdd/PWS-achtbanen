#pragma once

#include "ecs/Registry.h"
#include "Rigidbody.h"
#include "components/Transform.h"
#include "Collider.h"

namespace Physics {

	void updateRigidbodies(Registry& registry, float dt);

	void updateCollisions(Registry& registry, float dt);

};