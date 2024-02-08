#pragma once

#include "common.h"

#include "Mesh.h"
#include "Shader.h"
#include "Window.h"

using namespace math;

class Renderer2D
{
public:
	static void renderQuad(const Vec2& pos, const Vec2& dimensions, const Vec4& color);
	static void setResizeEvent(WindowResizeEvent* window);

private:
	static Mesh& quadMesh();
	static Shader& defaultShader();
	//static Shader& texturedShader();

	static void resizeCallback(int width, int height) { s_AspectRatio = float(width) / float(height); }

	static float s_AspectRatio;
	static WindowResizeEvent::Listener s_ResizeListener;
};