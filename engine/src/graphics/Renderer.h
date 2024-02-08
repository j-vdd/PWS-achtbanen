#pragma once

#include "Shader.h"
#include "Mesh.h"

#include "events/windowEvents.h"

#include "Camera.h"

#include "ecs/Registry.h"

#include "UniformBuffer.h"

class Renderer
{
public:
	Renderer();

	//void render(const Shader& shader, const Mesh& mesh, const Camera& camera);
	void render(const Mesh& mesh, const Shader& shader);
	void render(Registry& registry, const Camera& camera);

	void begin();
	void end();		//might do deferred rendering

	void clear();
	void setClearColor(float r, float g, float b, float a = 1.0f);

	void setLightDirection(const Vec3& direction);

	static void setViewPort(int width, int height);
	static void setResizeEvent(WindowResizeEvent* eventPtr);

private:
	UniformBuffer m_SceneBuffer;

	static WindowResizeEvent::Listener s_ResizeListener;
};