#pragma once

#include "common.h"

using namespace math;

class Rigidbody
{
public:
	Rigidbody()
		: invMass(1.0f), invInertia0(Mat3(1.0f)), friction(0.99f), angularFriction(0.99f)
	{}
	Rigidbody(float mass, const Mat3& inertiaTensor, float _friction, float _angularFriction) 
		: invMass(1.0f / mass), invInertia0(inverse(inertiaTensor)), friction(_friction), angularFriction(_angularFriction)
	{}

	void move(const Vec3& _force) { force += _force; }
	void rotate(const Vec3& _torque) { torque += _torque; }

	Vec3 linearMomentum{ 0 };
	Vec3 angularMomentum{ 0 };

	Vec3 force{ 0 };
	Vec3 torque{ 0 };

	//constants
	Mat3 invInertia0;
	float invMass, friction, angularFriction;
};