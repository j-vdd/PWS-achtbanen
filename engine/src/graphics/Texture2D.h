#pragma once

#include <string>

#include <glad/glad.h>

class Texture2D
{
public:
	Texture2D(const std::string& filepath);

	void bind(int slot) const;

private:
	void createTexture(uint8_t* data, GLenum internalFormat, GLenum dataFormat);

	int m_Width, m_Height;
	GLuint m_Texture;
};