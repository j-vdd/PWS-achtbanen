#pragma once

#include "Ref.h"
#include "Camera.h"
#include "physics/Rigidbody.h"

#include "common.h"

class Player
{
public:
	Player()
		: angularVelocity{ 0 }, rotation{ 0 }
	{}

	Vec3 angularVelocity;
	Vec3 rotation;
};