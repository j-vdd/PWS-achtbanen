#include "Renderer.h"

#include "components/Transform.h"
#include "RenderComponent.h"

WindowResizeEvent::Listener Renderer::s_ResizeListener;

Renderer::Renderer()
	: m_SceneBuffer("Scene")
{
	m_SceneBuffer.setLayout({ BufferElement("uSunDirection", BufferType::Float3) });
	m_SceneBuffer.set("uSunDirection", Vec3(0, -1, 0));
}

void Renderer::render(const Mesh& mesh, const Shader& shader)
{
	shader.use();
	mesh.bind();
	glDrawElements(GL_TRIANGLES, mesh.count(), GL_UNSIGNED_INT, nullptr);
	mesh.unbind();
}
void Renderer::render(Registry& registry, const Camera& camera)
{
	auto entities = registry.getEntities<Transform, RenderComponent>();

	for (Entity e : entities)
	{
		const auto& transform = registry.get<Transform>(e);
		const auto& renderComponent = registry.get<RenderComponent>(e);
		const auto& shader = renderComponent.material->getShader();

		shader->setUniform("uProjection", camera.projectionMatrix());
		shader->setUniform("uView", camera.viewMatrix());
		shader->setUniform("uModel", transform.modelMatrix()); //TODO: different way of setting model matrix, since this depends on user defined name
		shader->setUniform("uCameraPosition", camera.position);
		m_SceneBuffer.bindToShader(shader);

		renderComponent.use();
		glDrawElements(GL_TRIANGLES, renderComponent.mesh->count(), GL_UNSIGNED_INT, nullptr);
		renderComponent.unuse();
	}
}

void Renderer::clear()
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}
void Renderer::setClearColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
}

void Renderer::setLightDirection(const Vec3& direction)
{
	m_SceneBuffer.set("uSunDirection", normalize(direction));
}

void Renderer::setViewPort(int width, int height)
{
	glViewport(0, 0, width, height);
}

void Renderer::setResizeEvent(WindowResizeEvent* eventPtr)
{
	s_ResizeListener.setCallback(std::function<void(int, int)>(Renderer::setViewPort));
	s_ResizeListener.setEvent(eventPtr);
}