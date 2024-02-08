#pragma once

struct CartComponent
{
	CartComponent()
		: time(0.0f), velocity(0.0f), mass(1.0f), energy(0.0f)
	{}

	float time;
	float velocity;
	float mass;
	float energy;
};