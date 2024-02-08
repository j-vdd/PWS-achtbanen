#include "PhysicsManager.h"

namespace Physics {

	void updateRigidbodies(Registry& registry, float dt) //TODO: implement dt
	{
		// http://www.cs.cmu.edu/~baraff/sigcourse/notesd1.pdf
		// https://ubm-twvideo01.s3.amazonaws.com/o1/vault/gdc04/slides/using_verlet_integration.pdf

		auto entities = registry.getEntities<Transform, Rigidbody>();

		for (Entity e : entities)
		{
			auto& transform = registry.get<Transform>(e);
			auto& rigidbody = registry.get<Rigidbody>(e);


			// update position
			const Vec3 velocity = rigidbody.invMass * rigidbody.linearMomentum;
			const Vec3 acceleration = rigidbody.invMass * rigidbody.force;

			transform.position += velocity * dt + 0.5f * acceleration * dt * dt;
			rigidbody.linearMomentum = rigidbody.linearMomentum * rigidbody.friction + rigidbody.force * dt;


			// update rotation, TODO: tennis racket test
			const Mat3 rotationMat = mat3_cast(transform.rotation);
			const Mat3 invInertiaTensor = rotationMat * rigidbody.invInertia0 * transpose(rotationMat); //TODO: don't cast rotation to a 3x3 matrix
			const Vec3 angularVelocity = invInertiaTensor * rigidbody.angularMomentum;

			const Quatf angularVelocityQuat = 0.5f * transform.rotation * Quatf(0.0f, angularVelocity); //TODO: maybe swap order, depends on source
			const Quatf angularAccelerationQuat = 0.5f * transform.rotation * Quatf(-2.0f * dot(angularVelocityQuat, angularVelocityQuat), invInertiaTensor * rigidbody.torque);

			transform.rotation += angularVelocityQuat * dt + 0.5f * angularAccelerationQuat * dt * dt;
			rigidbody.angularMomentum = rigidbody.angularMomentum * rigidbody.angularFriction + rigidbody.torque * dt;


			// reset variables
			rigidbody.force = Vec3{ 0 };//Vec3{ 0, -0.005f, 0 };
			rigidbody.torque = Vec3{ 0 };
			transform.rotation = normalize(transform.rotation);
		}
	}

	struct CollisionInfo
	{
		bool hasCollided;
		Vec3 outVector;
	};
	
	//used for EPA
	struct Polytope
	{
	public:
		struct Face
		{
			Face()
				: i1(-1), i2(-1), i3(-1), distance(0.0f), normal(Vec3(0))
			{}
			Face(int _i1, int _i2, int _i3, float _distance, const Vec3& _normal)
				: i1(_i1), i2(_i2), i3(_i3), distance(_distance), normal(_normal)
			{}

			int i1, i2, i3;
			float distance;
			Vec3 normal;
		};

		Polytope(const Vec3& p1, const Vec3& p2, const Vec3& p3, const Vec3& p4)
			: m_Vertices{p1, p2, p3, p4}
		{
			//m_FurthestFaceIndex = m_ClosestFaceIndex = 0;

			int i1 = 0, i2 = 1, i3 = 2, i4 = 3;
			insertFaceClockwise(i1, i2, i3, p4);
			insertFaceClockwise(i1, i2, i4, p3);
			insertFaceClockwise(i1, i3, i4, p2);
			insertFaceClockwise(i2, i3, i4, p1);
		}

		//returns face closest to origin, with origin on the inside
		int getClosestFaceIndex() const 
		{
			int closest = -1;
			float closestDist = -INFINITY;

			for (int i = 0; i < m_Faces.size(); i++)
			{
				const auto& face = m_Faces[i];
				if (face.distance < 0.0f && face.distance > closestDist)
				{
					closest = i;
					closestDist = face.distance;
				}
			}

			return closest;
		}

		//returns face closest to origin, with origin on the outside
		int getFurthestFaceIndex() const {
			int closest = -1;
			float closestDist = INFINITY;

			for (int i = 0; i < m_Faces.size(); i++)
			{
				const auto& face = m_Faces[i];
				if (face.distance >= 0.0f && face.distance < closestDist)
				{
					closest = i;
					closestDist = face.distance;
				}
			}

			return closest;
		}

		const Face& getFace(int index) const
		{
			return m_Faces[index];
		}

		void insertPoint(int faceIndex, const Vec3& point)
		{
			m_Faces.push_back(Face()); m_Faces.push_back(Face()); //reserve faces, TODO: is there a method
			const Face& oldFace = m_Faces[faceIndex];

			//insert point
			m_Vertices.push_back(point);
			int pointIndex = (int)m_Vertices.size() - 1;

			//insert new faces, replace old face with first face
			insertFace((int)m_Faces.size() - 2, oldFace.i1, oldFace.i2, pointIndex);
			insertFace((int)m_Faces.size() - 1, oldFace.i2, oldFace.i3, pointIndex);
			insertFace(faceIndex, oldFace.i3, oldFace.i1, pointIndex);
		}

	private:
		void insertFaceClockwise(int i1, int i2, int i3, const Vec3& p4)
		{
			m_Faces.push_back(Face());
			const Vec3 p1 = m_Vertices[i1], p2 = m_Vertices[i2], p3 = m_Vertices[i3];

			if (dot(cross(p3 - p1, p2 - p1), p4 - p1) < 0.0f)
				insertFace(m_Faces.size() - 1, i1, i2, i3);
			else
				insertFace(m_Faces.size() - 1, i2, i1, i3); //switched order
		}
		void insertFace(int faceIndex, int i1, int i2, int i3)
		{
			//insert face
			Face& face = m_Faces[faceIndex];
			face.i1 = i1; face.i2 = i2; face.i3 = i3;

			const Vec3 p1 = m_Vertices[i1], p2 = m_Vertices[i2], p3 = m_Vertices[i3];

			face.normal = normalize(cross(p3 - p1, p2 - p1));
			face.distance = -dot(face.normal, p1); //any point works, not just p1

			//update furthest and closest
			/*if (face.distance < m_Faces[m_ClosestFaceIndex].distance)
				m_ClosestFaceIndex = faceIndex;

			if (face.distance > m_Faces[m_FurthestFaceIndex].distance)
				m_ClosestFaceIndex = faceIndex;*/
		}

		std::vector<Vec3> m_Vertices;

		std::vector<Face> m_Faces;

		//int m_FurthestFaceIndex, m_ClosestFaceIndex;
	};

	CollisionInfo AABB_AABB(const BaseCollider* colliderA, const Transform& transformA, const BaseCollider* colliderB, const Transform& transformB)
	{
		CollisionInfo collisionInfo;
		collisionInfo.hasCollided = false;

		return collisionInfo;
	}

	CollisionInfo GJK(const ColliderComponent& colliderA, const Transform& transformA, const ColliderComponent& colliderB, const Transform& transformB)
	{
		CollisionInfo collisionInfo;
		collisionInfo.hasCollided = false;

		const Mat3 rotA = transformA.rotationMatrix3x3();
		const Mat3 invRotA = transformA.inverseRotationMatrix3x3();
		const Mat3 rotB = transformB.rotationMatrix3x3();
		const Mat3 invRotB = transformB.inverseRotationMatrix3x3();

		auto calcSupportVector = [&](const Vec3& _dir)
			{
				const Vec3 supportA = rotA * colliderA.support(invRotA * _dir) + transformA.position;
				const Vec3 supportB = rotB * colliderB.support(invRotB * -_dir) + transformB.position;
				return supportA - supportB;
			};

		const Vec3 s1 = calcSupportVector(Vec3(1, 1, 1));
		const Vec3 s2 = calcSupportVector(Vec3(1, 1, -1));
		const Vec3 s3 = calcSupportVector(Vec3(-1, 1, 1));
		const Vec3 s4 = calcSupportVector(Vec3(-1, 1, -1));

		Vec3 direction = transformA.position - transformB.position; //TODO: parent position? also shouldn't be zero vector
		if (direction == Vec3(0.0f, 0.0f, 0.0f))
			direction = Vec3(0.1f, 0.2f, 0.3f); //just some random vector, not axis-aligned

		const Vec3 support1 = calcSupportVector(direction);
		if (dot(support1, direction) <= 0.0f)
			return collisionInfo;

		const Vec3 support2 = calcSupportVector(-direction);
		if (dot(support2, -direction) <= 0.0f)
			return collisionInfo;

		direction = cross(support2 - support1, cross(support1, support2 - support1));
		const Vec3 support3 = calcSupportVector(direction);
		if (dot(support3, direction) <= 0.0f)
			return collisionInfo;

		const Vec3 crossProd = cross(support2 - support1, support3 - support1);
		direction = dot(crossProd, support1) > 0.0f ? -crossProd : crossProd;
		const Vec3 support4 = calcSupportVector(direction);
		if (dot(support4, direction) <= 0.0f)
			return collisionInfo;

		Polytope polytope(support1, support2, support3, support4);

		//GJK
		int n = 0;
		while (n < 100)
		{
			n++;

			int nextFaceIndex = polytope.getFurthestFaceIndex();
			if (nextFaceIndex == -1) break; //polytope contains origin

			const Polytope::Face& face = polytope.getFace(nextFaceIndex);
			Vec3 support = calcSupportVector(face.normal);
			if (dot(support, face.normal) <= 0.0f)
			{
				return collisionInfo; //no collision
			}

			polytope.insertPoint(nextFaceIndex, support);
		}

		if (n >= 99)
			return collisionInfo;

		collisionInfo.hasCollided = true;

		//EPA
		n = 0;
		while (n < 100)
		{
			n++;

			int expandingFaceIndex = polytope.getClosestFaceIndex();

			const Polytope::Face& face = polytope.getFace(expandingFaceIndex);
			Vec3 support = calcSupportVector(face.normal);
			if (abs(-dot(support, face.normal) - face.distance) < 0.01f) //small margin to account for floating point errors, also makes algorithm terminate earlier
			{
				collisionInfo.outVector = face.normal * face.distance;
				break;
			}

			polytope.insertPoint(expandingFaceIndex, support);
		}

		return collisionInfo;
	}

	void updateCollisions(Registry& registry, float dt)
	{
		auto colliderEntities = registry.getEntities<ColliderComponent, Transform>();

		for (int i = 0; i < (int)colliderEntities.size() - 1; i++)
		{
			Entity e1 = colliderEntities[i];
			auto& collider1 = registry.get<ColliderComponent>(e1);
			auto& transform1 = registry.get<Transform>(e1);

			for (int j = i + 1; j < (int)colliderEntities.size(); j++)
			{
				Entity e2 = colliderEntities[j];
				auto& collider2 = registry.get<ColliderComponent>(e2);
				auto& transform2 = registry.get<Transform>(e2);

				CollisionInfo collisionInfo = GJK(collider1, transform1, collider2, transform2);
				if (collisionInfo.hasCollided)
				{
					bool e1HasPhysics = registry.hasComponent<Rigidbody>(e1);
					bool e2HasPhysics = registry.hasComponent<Rigidbody>(e2);
					if (e1HasPhysics && e2HasPhysics)
					{
						transform1.position += collisionInfo.outVector / 2.0f;
						transform2.position -= collisionInfo.outVector / 2.0f;
						const Vec3 outNormal = normalize(collisionInfo.outVector); //TODO: can be optimized

						auto& momentum1 = registry.get<Rigidbody>(e1).linearMomentum;
						momentum1 -= outNormal * dot(momentum1, outNormal);

						auto& momentum2 = registry.get<Rigidbody>(e2).linearMomentum;
						momentum2 -= outNormal * dot(momentum2, outNormal);
					}
					else if (e1HasPhysics)
					{
						transform1.position += collisionInfo.outVector;

						const Vec3 outNormal = normalize(collisionInfo.outVector); //TODO: can be optimized
						auto& momentum = registry.get<Rigidbody>(e1).linearMomentum;
						momentum -= outNormal * dot(momentum, outNormal);
					}
					else if (e2HasPhysics)
					{
						const Vec3 outNormal = normalize(collisionInfo.outVector); //TODO: can be optimized
						auto& momentum = registry.get<Rigidbody>(e2).linearMomentum;
						momentum -= outNormal * dot(momentum, outNormal);
						transform2.position -= collisionInfo.outVector;
					}
				}
			}
		}
	}

}