#include "UniformBuffer.h"

#include <iostream>

static uint32_t calcBaseAlignmentStd140(const BufferElement& element)
{
	if (element.Type == BufferType::None) return 0 * 4;
	if (element.Type == BufferType::Float || element.Type == BufferType::Int || element.Type == BufferType::Bool) return 1 * 4;
	if (element.Type == BufferType::Float2 || element.Type == BufferType::Int2) return 2 * 4;
	if (element.Type == BufferType::Float3 || element.Type == BufferType::Int3) return 4 * 4;
	if (element.Type == BufferType::Float4 || element.Type == BufferType::Int4) return 4 * 4;
	if (element.Type == BufferType::Float2x2) return 2 * 2 * 4;
	if (element.Type == BufferType::Float3x3) return 3 * 3 * 4;
	if (element.Type == BufferType::Float4x4) return 4 * 4 * 4;

	assert(false, "Incompatible element in uniform buffer layout");
	return 0;
}
static uint32_t calcSizeStd140(const BufferElement& element)
{
	uint32_t size = 0;

	if (element.Type == BufferType::Float || element.Type == BufferType::Int || element.Type == BufferType::Bool) size = 4;
	else if (element.Type == BufferType::Float2 || element.Type == BufferType::Int2) size = 2 * 4;
	else if (element.Type == BufferType::Float3 || element.Type == BufferType::Int3) size = 3 * 4;
	else if (element.Type == BufferType::Float4 || element.Type == BufferType::Int4) size = 4 * 4;
	else if (element.Type == BufferType::Float2x2) size = 2 * 2 * 4;
	else if (element.Type == BufferType::Float3x3) size = 4 * 3 * 4;
	else if (element.Type == BufferType::Float4x4) size = 4 * 4 * 4;

	assert(size != 0, "Incompatible element in uniform buffer layout.");
	return size * element.Length;
}

UniformBuffer::UniformBuffer(const std::string& name)
	: m_Name(name), m_RendererId(0), m_Size(0)
{
	initBuffer();
}
UniformBuffer::UniformBuffer(const std::string& name, const std::vector<BufferElement>& elements)
	: m_Name(name), m_RendererId(0), m_Size(0)
{
	initBuffer();

	setLayout(elements);
}
UniformBuffer::~UniformBuffer()
{
	glDeleteBuffers(1, &m_RendererId);
}

void UniformBuffer::setLayout(const std::vector<BufferElement>& elements)
{
	for (auto& element : elements)
		addElementStd140("", element);

	bind();
	glBufferData(GL_UNIFORM_BUFFER, m_Size, nullptr, GL_STATIC_DRAW);
	unbind();
}

void UniformBuffer::initBuffer()
{
	glGenBuffers(1, &m_RendererId);
	glBindBuffer(GL_UNIFORM_BUFFER, m_RendererId);

	static uint32_t s_Binding = 0;
	m_Binding = s_Binding++;
	glBindBufferBase(GL_UNIFORM_BUFFER, m_Binding, m_RendererId);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
void UniformBuffer::addElementStd140(const std::string& prefix, const BufferElement& element)
{
	// https://registry.khronos.org/OpenGL/extensions/ARB/ARB_uniform_buffer_object.txt
	uint32_t baseAlignment = calcBaseAlignmentStd140(element);

	uint32_t byteOffset = m_Size = baseAlignment * (m_Size / baseAlignment + (m_Size % baseAlignment != 0));//uint32_t(ceil(float(m_Size) / float(baseAlignment))) * baseAlignment;

	uint32_t elementSize = 0;
	if (element.Type == BufferType::Struct)
	{
		uint32_t originalSize = m_Size;
		for (auto& subElement : element.Elements)
			addElementStd140(prefix + element.Name + ".", subElement);

		elementSize = m_Size - originalSize;
	}
	else
	{
		elementSize = calcSizeStd140(element);
		m_Size += elementSize;//baseAlignment * (elementSize / baseAlignment + (elementSize % baseAlignment != 0));
	}

	m_Elements[prefix + element.Name] = ElementData(byteOffset, elementSize, element.Type);
}

void UniformBuffer::bindToShader(const Ref<Shader>& shader)
{
	uint32_t blockIndex = glGetUniformBlockIndex(shader->getId(), m_Name.c_str());

	assert(blockIndex != GL_INVALID_INDEX, "Invalid index");
	glUniformBlockBinding(shader->getId(), blockIndex, m_Binding);
}

void UniformBuffer::setUniform(const std::string& name, const void* data)
{
	//assert(m_Layout->Has(name), "Uniform with this name does not exist"); TODO

	auto& elementData = m_Elements[name];
	glBindBuffer(GL_UNIFORM_BUFFER, m_RendererId);
	glBufferSubData(GL_UNIFORM_BUFFER, elementData.Offset, elementData.Size, data);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UniformBuffer::bind() const
{
	glBindBuffer(GL_UNIFORM_BUFFER, m_RendererId);
}
void UniformBuffer::unbind() const
{
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}