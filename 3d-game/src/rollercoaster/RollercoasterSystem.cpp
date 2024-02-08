#include "RollercoasterSystem.h"

#include "components/Transform.h"

#include "CartComponent.h"

#include "Camera.h"
#include "Input.h"

namespace RollercoasterSystem
{
	void update(const Track& track, Registry& registry, float dt)
	{
		auto entities = registry.getEntities<CartComponent, Transform>();

		Vec3 position, normal;
		Quatf rotation;

		for (auto& e : entities)
		{
			auto& cart = registry.get<CartComponent>(e);
			auto& transform = registry.get<Transform>(e);

			cart.time += dt;
			auto& frame = track.getFrame(cart.time);

			position = frame.X;
			normal = frame.N;
			rotation = quat_cast(Mat3(
				-frame.B,
				frame.N,
				-frame.T
			));
			/*rotation = quat_cast(Mat3(
				1.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 1.0f
			));*/

			transform.position = position - 0.8f * normal;
			transform.rotation = rotation;
		}

		auto camEntity = registry.getEntities<Camera, Transform>()[0];
		auto& camera = registry.get<Camera>(camEntity);
		auto& transform = registry.get<Transform>(camEntity);
		if (Input::isPressed(GLFW_KEY_C)) {
			camera.rotation = rotation;// normalize(camera.rotation * 0.05f + rotation * 0.95f);
			camera.position = position;// +1.7f * normal;
			transform.position = camera.position;
		}
	}
	//void update(const Track& track, Registry& registry, float dt)
	//{
	//	auto entities = registry.getEntities<CartComponent, Transform>();

	//	Vec3 position, normal;
	//	Quatf rotation;

	//	for (auto& e : entities)
	//	{
	//		auto& cart = registry.get<CartComponent>(e);
	//		auto& transform = registry.get<Transform>(e);

	//		const float initialEnergy = 100.0f * cart.mass * 9.81f;

	//		cart.velocity = sqrt((initialEnergy - transform.position.y * 9.81f * cart.mass) * 2.0f / cart.mass); //1/2mv^2 + mgh = m * g * h_0
	//		cart.distance += dt * cart.velocity / length(track.sampleVelocity(cart.distance));
	//		transform.position = track.samplePosition(cart.distance);
	//		transform.rotation = quat_cast(track.sampleCartMatrix(cart.distance));

	//		position = transform.position;
	//		normal = track.sampleNormal(cart.distance, 10.0f);
	//		rotation = transform.rotation;

	//		//std::cout << cart.distance << std::endl;
	//		//std::cout << length(track.sampleAcceleration(cart.distance)) / length(track.sampleVelocity(cart.distance)) << std::endl;
	//	}

	//	auto camEntity = registry.getEntities<Camera, Transform>()[0];
	//	auto& camera = registry.get<Camera>(camEntity);
	//	auto& transform = registry.get<Transform>(camEntity);
	//	if (Input::isPressed(GLFW_KEY_C)) {
	//		camera.rotation = rotation;// normalize(camera.rotation * 0.05f + rotation * 0.95f);
	//		camera.position = position + 1.7f * normal;
	//		transform.position = camera.position;
	//	}
	//}
}