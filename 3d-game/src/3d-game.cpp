#include <iostream>


#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>

#include "graphics/Window.h"
#include "graphics/Shader.h"
#include "graphics/Mesh.h"
#include "graphics/Renderer.h"
#include "graphics/Renderer2d.h"
#include "graphics/RenderComponent.h"

#include "Camera.h"
#include "Player.h"
#include "PlayerSystem.h"

#include "Ref.h"

#include "events/Event.h"

#include "Input.h"

#include "physics/PhysicsManager.h"

#include "Gun.h"
#include "GunSystem.h"

#include "ecs/Registry.h"

#include "AssetManager.h"

#include "rollercoaster/Track.h"
#include "rollercoaster/CartComponent.h"
#include "rollercoaster/RollercoasterSystem.h"

#include "Sphere.h"

int main(int argc, char* argv[])
{
	std::string assetDirectory = "assets/";//"C:/dev/3d-game/3d-game/assets/";

	Ref<Window> window = CreateRef<Window>(1200, 900);
	window->enableVSync();
	//window->toggleFullScreen();

	AssetManager assetManager(assetDirectory);
	assetManager.loadTemplates("basic-assets.txt");

	Input::init(window->getWindowPtr());
	Renderer::setResizeEvent(&window->getResizeEvent());
	Renderer::setViewPort(window->getWidth(), window->getHeight());

	double time = glfwGetTime();

	Registry registry;
	Renderer renderer;

	//Ref<Mesh> obstacleMesh = CreateRef<Mesh>(assetDirectory + "cube.obj");
	//Ref<Material> obstacleMaterial = Material::create(assetManager.getEntityTemplate("obstacle"));

	std::vector<DVec3> rollercoasterPoints = {};
	{
		std::ifstream file(assetDirectory + "coaster.txt");
		assert(file.is_open());

		std::string line;
		while (std::getline(file, line))
		{
			if (line.size() == 0)
				break;

			std::stringstream lineStream(line);

			std::vector<std::string> keywords;
			std::string token;
			while (lineStream >> token)
			{
				keywords.push_back(token);
			}

			rollercoasterPoints.push_back(DVec3(
				std::stod(keywords[0]),
				std::stod(keywords[1]),
				std::stod(keywords[2])
			));
		}
	}

	Track track(rollercoasterPoints);
	/*Track track({ 
		{-9.810000, 0.000000, 0.000000},
		{0.000000, 0.000000, 2.000000},
		{-35.200035, 0.000000, 2.689998},
		{-35.200035, 0.000000, 1.000000},
		{-35.200035, 0.000000, 1.000000},
		{-35.200035, 0.000000, 1.000000},
		{-35.200035, 0.000000, 1.000000},
		{-35.200035, 0.000000, 1.000000},
	});*/
	/*Track track({
		{-9.810000, 0.000000, 0.000000},
		{0.000000, 0.000000, 2.000000},
		{-16.000025, 0.000000, 0.740000},
		{-32.800072, -0.820000, 1.000000},
		{-32.800072, -0.700000, 1.000000},
		{-32.800072, 0.660000, 1.000000},
		{-32.800072, 0.660000, 1.000000},
		{-1.599998, 0.660000, 1.000000},
		{-1.099998, -1.699999, 1.000000},
		{-31.500082, 0.660000, 1.000000},
		{-27.800068, -0.640000, 1.000000},
		{-16.600025, 0.440000, 1.000000},
		{-2.899998, 1.639999, 1.000000},
		{-24.700056, -1.559999, 1.000000},
		{-25.900061, 1.479999, 1.000000},
		{-25.900061, -1.559999, 1.000000},
		{-25.900061, -1.559999, 1.000000},
		{-25.900061, -1.559999, 1.000000},
		{-44.299896, 0.180000, 1.000000},
		{-44.299896, -0.260000, 1.000000},
		{-44.299896, -0.000000, 1.000000},
		{-13.300013, 0.699999, 1.000000},
		{-38.099991, 1.279999, 1.000000},
		{-38.099991, 1.279999, 1.000000},
		{-23.800053, -0.000000, 1.000000},
		{-38.099991, 1.279999, 1.000000},
	});*/
	/*Track track({
		{ -g, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 5.0f },
		{ -10.0f * g, 0.0f, 1.0f },
		{ -10.0f * g, 0.0f, 15.0f },
	});*/
	/*Track track({
		{-9.800000, 0.000000, 0.000000},
		{0.000000, 0.000000, 2.000000},
		{-27.500069, 0.000000, 1.000000},
		{-27.500069, 0.000000, 1.000000},
		{-27.500069, 0.000000, 1.000000},
		{-27.500069, -2.099999, 1.000000},
		{-27.500069, 0.000000, 1.000000},
		{-27.500069, 0.000000, 1.000000},
		{-27.500069, 0.000000, 1.000000},
		{-27.500069, 0.000000, 1.000000},
		{-27.500069, 0.000000, 1.000000},
		{-27.500069, 0.000000, 1.000000},
		{-27.500069, 0.000000, 1.000000},
		{-27.500069, 0.000000, 1.000000},
		{-27.500069, 0.000000, 1.000000},
		{-27.500069, 0.000000, 1.000000},
		{-27.500069, 0.000000, 1.000000},
		{-27.500069, 0.000000, 1.000000},
		{-27.500069, 0.000000, 1.000000},
		{-27.500069, 0.000000, 1.000000},
		{-27.500069, 0.000000, 1.000000},
		{-27.500069, 0.000000, 1.000000},
	});*/
	/*Track track({
		{-9.800000, 0.000000, 0.000000},
		{0.000000, 0.000000, 2.000000},
		{-19.600039, 0.000000, 0.730000},
		{-19.600039, 0.000000, 1.000000},
		{-24.500057, -0.920000, 1.000000},
		{-19.600039, -0.920000, 1.000000},
		{-19.900040, 0.480000, 1.000000},
		{-27.300068, -0.000000, 1.000000},
		{-27.300068, -0.000000, 1.000000},
		{-27.300068, -0.000000, 1.000000},
		{-27.300068, -0.000000, 1.000000},
		{-27.300068, -0.000000, 1.000000},
		{-27.300068, -0.000000, 1.000000},
		{3.799998, 1.299999, 1.000000},
		{-39.799965, 0.180000, 1.000000},
		{-39.799965, -0.020000, 1.000000},
		{-39.799965, -0.020000, 1.000000},
		{-39.799965, -0.020000, 1.000000},
		{-39.799965, -0.020000, 1.000000},
		{-39.799965, -0.020000, 1.000000},
	});*/

	Ref<Material> trackMaterial = Material::create(assetManager.getEntityTemplate("track"));

	Ref<Mesh> trackMesh = Mesh::create();
	track.generateMesh(trackMesh, trackMaterial);

	Entity obstacle = registry.create<Transform, RenderComponent>();
	registry.get<RenderComponent>(obstacle) = RenderComponent(trackMesh, trackMaterial);

	/*Sphere sphere(10.0f, 10);
	Ref<Mesh> sphereMesh = sphere.genMesh();
	Ref<Material> sphereMaterial = Material::create(assetManager.getAsset("sphereMaterial"));
	Entity spereE = registry.create<Transform, RenderComponent>();
	registry.get<RenderComponent>(spereE) = RenderComponent(sphereMesh, sphereMaterial);*/
	Ref<Mesh> graphMesh = Mesh::create();
	track.graphSpeed(graphMesh);
	Ref<Material> graphMaterial = Material::create(assetManager.getEntityTemplate("graph"));

	Entity graph = registry.create<Transform, RenderComponent>();
	registry.get<RenderComponent>(graph) = RenderComponent(graphMesh, graphMaterial);

	Ref<Mesh> cartMesh = Mesh::create(assetManager.getEntityTemplate("cart"));
	Ref<Material> cartMaterial = Material::create(assetManager.getEntityTemplate("cart"));

	Entity cart = registry.create<Transform, RenderComponent, CartComponent>();
	registry.get<RenderComponent>(cart) = RenderComponent(cartMesh, cartMaterial);
	registry.get<CartComponent>(cart).mass = 10000.0f;
	registry.get<Transform>(cart).scale = 0.7f;

	Ref<Mesh> groundMesh = Mesh::create(assetManager.getEntityTemplate("ground"));
	Ref<Material> groundMaterial = Material::create(assetManager.getEntityTemplate("ground"));
	Entity ground = registry.create<Transform, RenderComponent>();
	registry.get<RenderComponent>(ground) = RenderComponent(groundMesh, groundMaterial);
	registry.get<Transform>(ground).scale = 400.0f;

	Entity player = registry.create<Player, Camera, Transform, Rigidbody>();
	registry.get<Transform>(player).position = { 0.0f, 0.0f, 0.0f };
	registry.get<Rigidbody>(player) = Rigidbody(1.0f, Mat3(1.0f), 0.9f, 0.9f);
	
	auto& camera = registry.get<Camera>(player);
	camera.aspect = window->getAspect();
	camera.fov = 90.0f / 180.0f * 3.141592f;//1.3f;
	camera.setResizeEvent(&window->getResizeEvent());

	Renderer2D::setResizeEvent(&window->getResizeEvent());

	renderer.setLightDirection(normalize(Vec3(0.2f, -1.0f, 0.1f)));
	renderer.setClearColor(0.6f, 0.6f, 0.6f);

	float rotX = 0.0f, rotY = 0.0f;
	bool isPlusPressed = false;
	while (!window->getShouldClose()) {
		renderer.clear();

		PlayerSystem::update(registry, 1.0f);
		GunSystem::update(registry, 1.0f);

		Physics::updateRigidbodies(registry, 1.0f);
		Physics::updateCollisions(registry, 1.0f);

		RollercoasterSystem::update(track, registry, 1.0f / 60.0f);
		renderer.render(registry, camera);

		if (Input::isPressed(GLFW_KEY_KP_ADD) || Input::isPressed(GLFW_KEY_EQUAL))
		{
			if (!isPlusPressed)
			{
				track.incrementSegmentPointer(trackMesh, trackMaterial, graphMesh);
				isPlusPressed = true;
			}
		}
		else if (Input::isPressed(GLFW_KEY_KP_SUBTRACT) || Input::isPressed(GLFW_KEY_MINUS))
		{
			if (!isPlusPressed)
			{
				track.decrementSegmentPointer(trackMesh, trackMaterial);
				isPlusPressed = true;
			}
		}
		else if (Input::isPressed(GLFW_KEY_R))
		{
			track.graphSpeed(graphMesh);
		}
		else
		{
			isPlusPressed = false;
		}

		if (Input::isPressed(GLFW_KEY_KP_8) || Input::isPressed(GLFW_KEY_6))
		{
			track.changeLastSegment(trackMesh, trackMaterial, -0.1f, 0.0f, 0.0f, graphMesh);
		}
		if (Input::isPressed(GLFW_KEY_KP_5) || Input::isPressed(GLFW_KEY_5))
		{
			track.changeLastSegment(trackMesh, trackMaterial, 0.1f, 0.0f, 0.0f, graphMesh);
		}
		if (Input::isPressed(GLFW_KEY_KP_4) || Input::isPressed(GLFW_KEY_7))
		{
			track.changeLastSegment(trackMesh, trackMaterial, 0.0f, -0.02f, 0.0f, graphMesh);
		}
		if (Input::isPressed(GLFW_KEY_KP_6) || Input::isPressed(GLFW_KEY_8))
		{
			track.changeLastSegment(trackMesh, trackMaterial, 0.0f, 0.02f, 0.0f, graphMesh);
		}
		if (Input::isPressed(GLFW_KEY_KP_7) || Input::isPressed(GLFW_KEY_9))
		{
			track.changeLastSegment(trackMesh, trackMaterial, 0.0f, 0.0f, -0.01f, graphMesh);
		}
		if (Input::isPressed(GLFW_KEY_KP_9) || Input::isPressed(GLFW_KEY_0))
		{
			track.changeLastSegment(trackMesh, trackMaterial, 0.0f, 0.0f, 0.01f, graphMesh);
		}
		if (Input::isPressed(GLFW_KEY_P))
		{
			registry.get<Player>(player).rotation = Vec3(-3.141592f / 2.0f, 0, 0);
		}

		if (Input::isPressed(GLFW_KEY_C))
		{
			registry.get<Transform>(cart).scale = 0.0f;
		}
		else
		{
			registry.get<Transform>(cart).scale = 0.7f;
		}

		if (Input::isPressed(GLFW_KEY_V))
		{
			std::cout << track.save() << std::endl;
		}

		if (Input::isPressed(GLFW_KEY_COMMA))
			groundMaterial->set("smallGridEnabled", 0.0f);
		if (Input::isPressed(GLFW_KEY_PERIOD))
			groundMaterial->set("smallGridEnabled", 1.0f);

		//Renderer2D::renderQuad({ -0.02f, -0.001f }, { 0.04f, 0.002f }, { 1, 1, 1, 1 });
		//Renderer2D::renderQuad({ -0.001f, -0.02f }, { 0.002f, 0.04f }, { 1, 1, 1, 1 });

		window->onFrameEnd();
	}
}