#pragma once

#include "common.h"

using namespace math;

//TODO: make system to update matrices each frame.
struct Transform
{
	Transform()
		: position{ 0 }, rotation(Vec3{ 0 }), scale(1.0f), parent(nullptr)
	{}

	Vec3 position;
	Quatf rotation;
	float scale;
	Transform* parent;

	Mat4 modelMatrix() const {
		if (parent)
			return modelTransform(position, rotation, scale) * parent->modelMatrix();
		
		return modelTransform(position, rotation, scale); 
	}
	Mat4 inverseModelMatrix() const {
		if (parent)
			return parent->inverseModelMatrix() * inverseModelTransform(position, rotation, scale);

		return inverseModelTransform(position, rotation, scale);
	}

	Mat3 rotationMatrix3x3() const {
		if (parent)
			return mat3_cast(rotation) * parent->rotationMatrix3x3();

		return mat3_cast(rotation);
	}
	Mat3 inverseRotationMatrix3x3() const {
		if (parent)
			return parent->inverseRotationMatrix3x3() * mat3_cast(conjugate(rotation));

		return mat3_cast(conjugate(rotation));
	}
};