#pragma once

#include <vector>

class MeshView
{
public:
	MeshView(const std::vector<float>& vertices, const std::vector<uint32_t>& indices, const std::vector<uint32_t>& layout = { 3 })
		: m_Vertices(vertices), m_Indices(indices), m_Layout(layout)
	{}

	const std::vector<float>& getVertices() const { return m_Vertices; }
	const std::vector<uint32_t>& getIndices() const { return m_Indices; }
	const std::vector<uint32_t>& getLayout() const { return m_Layout; }
	uint32_t getCount() const { return (uint32_t)m_Indices.size(); }

private:
	std::vector<float> m_Vertices;
	std::vector<uint32_t> m_Indices;
	std::vector<uint32_t> m_Layout; //TODO: is uint32_t necessary?
};