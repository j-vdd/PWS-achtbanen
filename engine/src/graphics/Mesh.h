#pragma once

#include <vector>
#include <string>

#include <glad/glad.h>

#include "Ref.h"
#include "MeshView.h"

#include "AssetManager.h"

class Mesh 
{
public:
	Mesh();
	//Mesh(const MeshView& meshView);
	Mesh(const std::string& filepath);
	Mesh(const std::vector<float>& vertices, const std::vector<uint32_t>& indices, const std::vector<uint32_t>& layout = { 3 });

	static Ref<Mesh> create();
	static Ref<Mesh> create(const std::vector<float>& vertices, const std::vector<uint32_t>& indices, const std::vector<uint32_t>& layout = { 3 });
	static Ref<Mesh> create(const AssetManager::EntityTemplate& entityTemplate);

	Mesh(const Mesh&&) = delete;
	Mesh(const Mesh&) = delete;
	~Mesh();

	void bind() const;
	void unbind() const;
	uint32_t count() const { return m_Count; }

	void setShape(const std::vector<float>& vertices, const std::vector<uint32_t>& indices);
	void setLayout(const std::vector<uint32_t>& layout);

private:
	void initBuffers();

	std::vector<uint32_t> m_Layout;

	GLuint m_Vao, m_Vbo, m_Ebo;

	uint32_t m_Count;
};