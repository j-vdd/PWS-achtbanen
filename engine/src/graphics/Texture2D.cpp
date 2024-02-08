#include "Texture2D.h"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture2D::Texture2D(const std::string& filepath)
	: m_Texture(0)
{
	int channels;
	stbi_set_flip_vertically_on_load(true);
	stbi_uc* data = stbi_load(filepath.c_str(), &m_Width, &m_Height, &channels, 0);
	if (!data)
		std::cout << "failed to load texture: " << filepath << std::endl;

	GLenum internalFormat = 0, dataFormat = 0;
	if (channels == 3)
	{
		internalFormat = GL_RGB8;
		dataFormat = GL_RGB;
	}
	else if (channels == 4)
	{
		internalFormat = GL_RGBA8;
		dataFormat = GL_RGBA;
	}
	else
		std::cout << "Invalid number of channels in texture: " << filepath << std::endl;

	createTexture(data, internalFormat, dataFormat);

	stbi_image_free(data);
}

void Texture2D::createTexture(uint8_t* data, GLenum internalFormat, GLenum dataFormat)
{
	glGenTextures(1, &m_Texture);
	glBindTexture(GL_TEXTURE_2D, m_Texture);
	glTexStorage2D(GL_TEXTURE_2D, 1, internalFormat, m_Width, m_Height);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);
}

void Texture2D::bind(int slot) const
{
	//glBindTextureUnit(slot, m_Texture);
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_Texture);
}