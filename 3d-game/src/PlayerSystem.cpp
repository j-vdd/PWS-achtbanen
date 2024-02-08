#include "PlayerSystem.h"

#include "Input.h"
#include "physics/Rigidbody.h"
#include "components/Transform.h"
#include "graphics/RenderComponent.h"
#include "Player.h"
#include "Gun.h"
#include "physics/Collider.h"

void PlayerSystem::update(Registry& registry, float dt)
{
	Entity e = registry.getEntity<Player, Rigidbody, Transform, Camera>();
	if (e == 0) return;

	auto& player = registry.get<Player>(e);
	auto& transform = registry.get<Transform>(e);
	auto& rigidbody = registry.get<Rigidbody>(e);
	auto& camera = registry.get<Camera>(e);

	Vec3 acceleration(0.0f);
	Vec3 torque(0.0f);

	if (Input::isPressed(GLFW_KEY_W)) {
		acceleration.z -= 1.f;
	}
	if (Input::isPressed(GLFW_KEY_A)) {
		acceleration.x -= 1.f;
	}
	if (Input::isPressed(GLFW_KEY_S)) {
		acceleration.z += 1.f;
	}
	if (Input::isPressed(GLFW_KEY_D)) {
		acceleration.x += 1.f;
	}
	if (Input::isPressed(GLFW_KEY_SPACE))
		acceleration.y += 1.f;
	if (Input::isPressed(GLFW_KEY_LEFT_SHIFT))
		acceleration.y -= 1.f;

	if (Input::isPressed(GLFW_KEY_I))
		torque.x -= 1.f;
	if (Input::isPressed(GLFW_KEY_J))
		torque.y -= 1.f;
	if (Input::isPressed(GLFW_KEY_K))
		torque.x += 1.f;
	if (Input::isPressed(GLFW_KEY_L))
		torque.y += 1.f;

	if (length(acceleration) != 0.0f)
	{
		float theta = -player.rotation.y;
		Mat3 vertRotation = Mat3(
			cos(theta), 0, -sin(theta),
			0, 1, 0,
			sin(theta), 0, cos(theta)
		);
		acceleration = normalize(Vec3(acceleration.x, 0.0f, acceleration.z) * vertRotation + Vec3(0.0f, acceleration.y, 0.0f)) * 0.05f;
	}
		//acceleration = normalize(Vec3(acceleration.x, 0.0f, acceleration.z) * inverse(mat3_cast(Quatf(player.rotation))) + Vec3(0.0f, acceleration.y, 0.0f)) * 0.05f;

	if (length(torque) != 0.0f)
		torque = -normalize(torque) * 0.005f;

	player.rotation += player.angularVelocity * dt + torque * dt * dt;
	player.angularVelocity = player.angularVelocity * 0.85f + torque * dt;

	rigidbody.move(acceleration);

	//TODO: sync?
	camera.position = transform.position;
	transform.rotation = camera.rotation = Quatf(player.rotation);

	/*if (Input::isPressed(GLFW_KEY_SPACE) && gun.canFire())
	{
		gun.onFire();

		static Ref<Mesh> bulletMesh = CreateRef<Mesh>(
			std::vector<float>({
				-.1f, -.1f, 0.f,
				-.1f, .1f, 0.f,
				.1f, -.1f, 0.f,
				.1f, .1f, 0.f
			}),
			std::vector<uint32_t>({
				0, 1, 2,
				1, 2, 3
			}),
			std::vector<uint32_t>({ 3 })
		);
		static Ref<Shader> bulletShader = CreateRef<Shader>("C:/dev/3d-game/3d-game/src/shaders/basic");
		static Ref<Material> material = CreateRef<Material>(bulletShader, std::vector<BufferElement>{ BufferElement("color", BufferType::Float3) });
		material->set("color", Vec3(1.0f, 0.0f, 0.0f));

		Entity bullet = registry.create<Transform, Rigidbody, RenderComponent, ColliderComponent>();
		registry.get<ColliderComponent>(bullet) = ColliderComponent(Vec3(-0.1f), Vec3(0.1f));
		registry.get<RenderComponent>(bullet) = RenderComponent(bulletMesh, material);
		
		const Vec3 bulletDirection = Vec3(0, 0, -1) * inverse(mat3_cast(Quatf(player.rotation)));
		registry.get<Transform>(bullet).position = transform.position + 1.5f * bulletDirection;
		registry.get<Transform>(bullet).rotation = camera.rotation;

		auto& bulletRigidbody = registry.get<Rigidbody>(bullet);
		bulletRigidbody.linearMomentum = bulletDirection;
		bulletRigidbody.friction = 1.0f;
	}
	if (Input::isPressed(GLFW_KEY_R))
	{
		gun.onReload();
	}*/
}