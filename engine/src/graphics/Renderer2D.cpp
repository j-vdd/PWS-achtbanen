#include "Renderer2d.h"

#include "Mesh.h"

float Renderer2D::s_AspectRatio = 1.0f;
WindowResizeEvent::Listener Renderer2D::s_ResizeListener;

void Renderer2D::setResizeEvent(WindowResizeEvent* resizeEvent)
{
	s_ResizeListener = WindowResizeEvent::Listener(resizeEvent, std::bind(&Renderer2D::resizeCallback, std::placeholders::_1, std::placeholders::_2));
}

Mesh& Renderer2D::quadMesh()
{
	static Mesh mesh(
		{
			0.f, 0.f,
			0.f, 1.f,
			1.f, 0.f,
			1.f, 1.f
		},
		{
			0, 1, 2,
			1, 2, 3
		},
		{ 2 }
	);
	return mesh;
}
Shader& Renderer2D::defaultShader()
{
	static Shader shader("C:/dev/3d-game/engine/src/graphics/shaders/defaultShader2d");
	return shader;
}

void Renderer2D::renderQuad(const Vec2& pos, const Vec2& dimensions, const Vec4& color)
{
	auto& shader = defaultShader();
	auto& mesh = quadMesh();

	Vec2 aspectScale = Vec2(1.0f, s_AspectRatio);
	shader.setUniform("uPosition", pos * aspectScale);
	shader.setUniform("uDimensions", dimensions * aspectScale);
	shader.setUniform("uColor", color);

	shader.use();
	mesh.bind();
	glDrawElements(GL_TRIANGLES, mesh.count(), GL_UNSIGNED_INT, nullptr);
	mesh.unbind();
}