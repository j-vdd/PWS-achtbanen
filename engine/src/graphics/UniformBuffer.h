#pragma once

#include <assert.h>

#include "Ref.h"
#include "Shader.h"
#include "Types.h"

class UniformBuffer
{
public:
	UniformBuffer(const std::string& name);
	UniformBuffer(const std::string& name, const std::vector<BufferElement>& elements);
	~UniformBuffer();

	void setLayout(const std::vector<BufferElement>& elements);

	void bindToShader(const Ref<Shader>& shader);

	void set(const std::string& name, float value) { setUniform(name, &value); }
	void set(const std::string& name, const Vec2& value) { setUniform(name, &value); }
	void set(const std::string& name, const Vec3& value) { setUniform(name, &value); }
	void set(const std::string& name, const Vec4& value) { setUniform(name, &value); }

	void set(const std::string& name, int value) { setUniform(name, &value); }
	void set(const std::string& name, const IVec2& value) { setUniform(name, &value); }
	void set(const std::string& name, const IVec3& value) { setUniform(name, &value); }
	void set(const std::string& name, const IVec4& value) { setUniform(name, &value); }

	void set(const std::string& name, bool value) { setUniform(name, &value); }

	uint32_t getSize() const { return m_Size; }

	void bind() const;
	void unbind() const;

private:
	struct ElementData {
		uint32_t Offset;
		uint32_t Size;
		BufferType Type;
	};

	void initBuffer();
	void setUniform(const std::string& name, const void* data); //this is private, since it makes sure 3x3 matrices are passed correctly
	void addElementStd140(const std::string& prefix, const BufferElement& element);

private:
	std::unordered_map<std::string, ElementData> m_Elements;
	std::string m_Name;

	uint32_t m_Size;
	GLuint m_RendererId;
	GLuint m_Binding;
};