#pragma once

#include <iostream>

#include "Ref.h"

#include "common.h"

using namespace math;

//TODO: include spatial partitioning tree data
class ColliderComponent
{
public:
	ColliderComponent()
		: m_Min(Vec3()), m_Max(Vec3())
	{}
	ColliderComponent(const Vec3& min, const Vec3& max)
		: m_Min(min), m_Max(max)
	{}

	Vec3 support(const Vec3& direction) const
	{
		return Vec3(
			direction.x < 0.0f ? m_Min.x : m_Max.x,
			direction.y < 0.0f ? m_Min.y : m_Max.y,
			direction.z < 0.0f ? m_Min.z : m_Max.z
		);
	}

private:
	Vec3 m_Min;
	Vec3 m_Max;
};

enum class ColliderType
{
	CONVEX, AABB, BOX, SPHERE
};

class BaseCollider
{
public:
	BaseCollider(ColliderType type)
		: m_Type(type)
	{}

	virtual Vec3 support(const Vec3& direction) const = 0;
	virtual Vec3 support(const Vec3& direction, const Mat3& rotation, const Mat3& invRotation) const = 0;

	ColliderType type() const { return m_Type; }

protected:
	ColliderType m_Type;
};

class SphereCollider : public BaseCollider
{
public:
	SphereCollider()
		: m_Radius(0.0f), BaseCollider(ColliderType::SPHERE)
	{}
	SphereCollider(const std::vector<Vec3>& vertices)
		: BaseCollider(ColliderType::SPHERE)
	{
		m_Radius = INFINITY;
		for (auto& vertex : vertices)
			m_Radius = std::min(m_Radius, length(vertex));
	}
	SphereCollider(const Vec3& center, float radius)
		: m_Radius(radius), BaseCollider(ColliderType::SPHERE)
	{}

	Vec3 support(const Vec3& direction) const override
	{
		return normalize(direction) * m_Radius;
	}
	Vec3 support(const Vec3& direction, const Mat3& rotation, const Mat3& invRotation) const override
	{
		return support(direction);
	}

	float getRadius() const { return m_Radius; }

private:
	float m_Radius;
};
class AABBCollider : public BaseCollider
{
public:
	AABBCollider()
		: m_Min(Vec3()), m_Max(Vec3()), BaseCollider(ColliderType::AABB)
	{}
	AABBCollider(const std::vector<Vec3>& vertices)
		: m_Min(INFINITY), m_Max(-INFINITY), BaseCollider(ColliderType::AABB)
	{
		for (auto& vertex : vertices)
		{
			addVertex(vertex);
		}
	}
	AABBCollider(const Vec3& min, const Vec3& max)
		: m_Min(min), m_Max(max), BaseCollider(ColliderType::AABB)
	{}

	Vec3 support(const Vec3& direction) const override
	{
		return Vec3(
			direction.x < 0.0f ? m_Min.x : m_Max.x,
			direction.y < 0.0f ? m_Min.y : m_Max.y,
			direction.z < 0.0f ? m_Min.z : m_Max.z
		);
	}
	Vec3 support(const Vec3& direction, const Mat3& rotation, const Mat3& invRotation) const override
	{
		return support(direction);
	}

	const Vec3& getMin() const { return m_Min; }
	const Vec3& getMax() const { return m_Max; }

	void addVertex(const Vec3& vertex)
	{
		m_Min = min(m_Min, vertex);
		m_Max = max(m_Max, vertex);
	}

private:
	Vec3 m_Min;
	Vec3 m_Max;
};
class BoxCollider : public BaseCollider
{
public:
	BoxCollider()
		: m_Min(Vec3()), m_Max(Vec3()), BaseCollider(ColliderType::BOX)
	{}
	BoxCollider(const std::vector<Vec3>& vertices)
		: m_Min(INFINITY), m_Max(-INFINITY), BaseCollider(ColliderType::BOX)
	{
		for (auto& vertex : vertices)
		{
			m_Min = min(m_Min, vertex);
			m_Max = max(m_Max, vertex);
		}
	}
	BoxCollider(const Vec3& min, const Vec3& max)
		: m_Min(min), m_Max(max), BaseCollider(ColliderType::BOX)
	{}

	Vec3 support(const Vec3& direction) const override
	{
		return Vec3(
			direction.x < 0.0f ? m_Min.x : m_Max.x,
			direction.y < 0.0f ? m_Min.y : m_Max.y,
			direction.z < 0.0f ? m_Min.z : m_Max.z
		);
	}
	Vec3 support(const Vec3& direction, const Mat3& rotation, const Mat3& invRotation) const override
	{
		const Vec3 rotatedDir = invRotation * direction;
		
		return rotation * support(rotatedDir);
	}

	const Vec3& getMin() const { return m_Min; }
	const Vec3& getMax() const { return m_Max; }

private:
	Vec3 m_Min;
	Vec3 m_Max;
};
class ConvexCollider : public BaseCollider
{
public:
	ConvexCollider()
		: m_Vertices{}, BaseCollider(ColliderType::CONVEX)
	{}
	ConvexCollider(const std::vector<Vec3>& vertices)
		: m_Vertices(vertices), BaseCollider(ColliderType::CONVEX)
	{}

	Vec3 support(const Vec3& direction) const override
	{
		Vec3 bestVertex(0);
		float bestDistance = -INFINITY;
		for (const Vec3& v : m_Vertices)
		{
			float d = dot(v, direction);
			if (d > bestDistance)
			{
				bestVertex = v;
				bestDistance = d;
			}
		}

		return bestVertex;
	}
	Vec3 support(const Vec3& direction, const Mat3& rotation, const Mat3& invRotation) const override
	{
		const Vec3 rotatedDir = invRotation * direction;

		return rotation * support(rotatedDir);
	}

private:
	std::vector<Vec3> m_Vertices;
};


class Collider
{
public:
	Collider()
		: m_Colliders()
	{}

	void addCollider(const Ref<BaseCollider>& collider) { 
		m_Colliders.push_back(collider);

		m_BoundingBox.addVertex(collider->support(Vec3(1, 0, 0)));
		m_BoundingBox.addVertex(collider->support(Vec3(-1, 0, 0)));
		m_BoundingBox.addVertex(collider->support(Vec3(0, 1, 0)));
		m_BoundingBox.addVertex(collider->support(Vec3(0, -1, 0)));
		m_BoundingBox.addVertex(collider->support(Vec3(0, 0, 1)));
		m_BoundingBox.addVertex(collider->support(Vec3(0, 0, -1)));
	}

	//could be used for broad phase collision detection
	const AABBCollider& getBoundingBox() const { return m_BoundingBox; }

	const std::vector<Ref<BaseCollider>>& getCollider() const { return m_Colliders; }

private:
	AABBCollider m_BoundingBox;
	std::vector<Ref<BaseCollider>> m_Colliders;
};