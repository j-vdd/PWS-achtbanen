#include "Mesh.h"

#include <iostream>
#include <fstream>
#include <sstream>

Mesh::Mesh()
	: m_Layout{3}, m_Vao(0), m_Vbo(0), m_Ebo(0), m_Count(0)
{
	initBuffers();
}
//Mesh::Mesh(const MeshView& meshView)
//	: m_Layout(meshView.getLayout()), m_Vao(0), m_Vbo(0), m_Ebo(0), m_Count(meshView.getCount())
//{
//	initBuffers();
//	setShape(meshView.getVertices(), meshView.getIndices());
//	setLayout(meshView.getLayout());
//}

Mesh::Mesh(const std::string& filepath)
{
	initBuffers();

	std::ifstream file(filepath);

	if (!file.is_open())
		return;

	std::vector<float> positions;
	std::vector<float> normals;
	std::vector<float> uvCoords;

	std::vector<std::tuple<size_t, size_t, size_t>> vertexIndices;

	std::vector<uint32_t> indices;

	auto parseIndex = [&](const std::string& index)
		{
			size_t firstSlash = index.find_first_of('/');
			size_t secondSlash = index.find_last_of('/');

			size_t positionIndex = std::stoull(index.substr(0, firstSlash)) - 1ULL;
			size_t uvIndex = std::stoull(index.substr(firstSlash + 1, secondSlash - firstSlash - 1)) - 1ULL;
			size_t normalIndex = std::stoull(index.substr(secondSlash + 1, index.size() - secondSlash - 1)) - 1ULL;

			std::tuple<size_t, size_t, size_t> vertexIndex(positionIndex, normalIndex, uvIndex);
			/*for (size_t i = 0; i < vertexIndices.size(); i++)
			{
				if (vertexIndices[i] == vertexIndex)
					return i;
			}*/

			vertexIndices.push_back(vertexIndex);
			return vertexIndices.size() - 1ULL;
		};

	size_t vertexCount = 0, normalCount = 0, uvCount = 0;

	std::string line;
	while (std::getline(file, line))
	{
		std::stringstream lineStream(line);

		std::string token;
		lineStream >> token;
		if (token == "v")
		{
			positions.resize(positions.size() + 3);

			lineStream >> token; positions[vertexCount + 0] = std::stof(token);
			lineStream >> token; positions[vertexCount + 1] = std::stof(token);
			lineStream >> token; positions[vertexCount + 2] = std::stof(token);
			//std::cout << "vertex: " << positions[vertexCount + 0] << ", " << positions[vertexCount + 1] << ", " << positions[vertexCount + 2] << std::endl;
			vertexCount += 3;
		}
		else if (token == "vn")
		{
			normals.resize(normals.size() + 3);

			lineStream >> token; normals[normalCount + 0] = std::stof(token);
			lineStream >> token; normals[normalCount + 1] = std::stof(token);
			lineStream >> token; normals[normalCount + 2] = std::stof(token);
			normalCount += 3;
		}
		else if (token == "vt")
		{
			uvCoords.resize(uvCoords.size() + 2);

			lineStream >> token; uvCoords[uvCount + 0] = std::stof(token);
			lineStream >> token; uvCoords[uvCount + 1] = std::stof(token);
			uvCount += 2;
		}
		else if (token == "f")
		{
			std::string face1, face2, face3;
			lineStream >> face1; lineStream >> face2; lineStream >> face3;

			indices.push_back(parseIndex(face1));
			indices.push_back(parseIndex(face2));
			indices.push_back(parseIndex(face3));
		}
	}

	std::vector<float> vertices;
	vertices.resize(vertexIndices.size() * 8);
	for (size_t i = 0; i < vertexIndices.size(); i++)
	{
		auto& vertexIndex = vertexIndices[i];

		vertices[i * 8 + 0] = positions[std::get<0>(vertexIndex) * 3 + 0];
		vertices[i * 8 + 1] = positions[std::get<0>(vertexIndex) * 3 + 1];
		vertices[i * 8 + 2] = positions[std::get<0>(vertexIndex) * 3 + 2];

		vertices[i * 8 + 3] = normals[std::get<1>(vertexIndex) * 3 + 0];
		vertices[i * 8 + 4] = normals[std::get<1>(vertexIndex) * 3 + 1];
		vertices[i * 8 + 5] = normals[std::get<1>(vertexIndex) * 3 + 2];

		vertices[i * 8 + 6] = uvCoords[std::get<2>(vertexIndex) * 2 + 0];
		vertices[i * 8 + 7] = uvCoords[std::get<2>(vertexIndex) * 2 + 1];
	}

	setShape(vertices, indices);
	setLayout({ 3, 3, 2 });

	file.close();
}
Mesh::Mesh(const std::vector<float>& vertices, const std::vector<uint32_t>& indices, const std::vector<uint32_t>& layout)
	: m_Layout(layout), m_Vao(0), m_Vbo(0), m_Ebo(0), m_Count((uint32_t)indices.size())
{
	initBuffers();
	setShape(vertices, indices);
	setLayout(layout);
}

Ref<Mesh> Mesh::create()
{
	return CreateRef<Mesh>();
}
Ref<Mesh> Mesh::create(const std::vector<float>& vertices, const std::vector<uint32_t>& indices, const std::vector<uint32_t>& layout)
{
	return CreateRef<Mesh>(vertices, indices, layout);
}
Ref<Mesh> Mesh::create(const AssetManager::EntityTemplate& entityTemplate)
{
	assert(entityTemplate.has("Mesh"));
	return CreateRef<Mesh>(entityTemplate.assets.at("Mesh").properties.at("objPath").value + ".obj");
}

Mesh::~Mesh() 
{
	glDeleteVertexArrays(1, &m_Vao);
}

void Mesh::initBuffers()
{
	glGenVertexArrays(1, &m_Vao);
	glBindVertexArray(m_Vao);

	glGenBuffers(1, &m_Ebo);
	glGenBuffers(1, &m_Vbo);

	glBindVertexArray(0);
}

void Mesh::setShape(const std::vector<float>& vertices, const std::vector<uint32_t>& indices)
{
	m_Count = (uint32_t)indices.size();

	glBindVertexArray(m_Vao);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	glBindVertexArray(0);

	setLayout(m_Layout);
}
void Mesh::setLayout(const std::vector<uint32_t>& layout)
{
	bind();

	m_Layout = layout;

	size_t offset = 0;
	uint32_t totalStride = 0;
	for (auto element : layout)
		totalStride += element * sizeof(float);

	for (int i = 0; i < layout.size(); i++)
	{
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, layout[i], GL_FLOAT, GL_FALSE, totalStride, (void*)offset);
		offset += layout[i] * sizeof(float);
	}

	unbind();
}

void Mesh::bind() const
{
	glBindVertexArray(m_Vao);
}
void Mesh::unbind() const
{
	glBindVertexArray(0);
}