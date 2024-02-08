#pragma once

#include <string>
#include <unordered_map>

#include <glad/glad.h>

#include "common.h"

using namespace math;

class Shader
{
public:
	Shader() = delete;
	Shader(const std::string& shaderPath);
	Shader(Shader&) = delete;
	~Shader();

	void use() const;

	void setUniform(const std::string& name, float v0) const;
	void setUniform(const std::string& name, float v0, float v1) const;
	void setUniform(const std::string& name, float v0, float v1, float v2) const;
	void setUniform(const std::string& name, float v0, float v1, float v2, float v3) const;
	void setUniform(const std::string& name, const Vec2& value) const;
	void setUniform(const std::string& name, const Vec3& value) const;
	void setUniform(const std::string& name, const Vec4& value) const;
	void setUniform(const std::string& name, const Mat2& value) const;
	void setUniform(const std::string& name, const Mat3& value) const;
	void setUniform(const std::string& name, const Mat4& value) const;

	GLuint getId() const { return m_Program; }

private:
	GLint location(const std::string& name) const;

	std::unordered_map<std::string, GLint> m_UniformLocations;

	GLuint m_Program;
};