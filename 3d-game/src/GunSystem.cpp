#include "GunSystem.h"

#include "Gun.h"

void GunSystem::update(Registry& registry, float dt)
{
	auto entities = registry.getEntities<Gun>();

	for (Entity e : entities)
	{
		auto& gun = registry.get<Gun>(e);

		gun.timer -= dt * (gun.timer >= 0.0f); //is overflowing an issue?
		if (gun.ammunition == 0)
			gun.onReload();
	}
}