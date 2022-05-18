#include "Texture.h"


Texture::Texture(const char* fileName)
{
	int w = 0;
	int h = 0;

	unsigned char* data = stbi_load(fileName, &w, &h, NULL, 4);

	if (!data)
	{
		throw std::runtime_error("data not found!!!");
	}



	id = 0;
	glGenTextures(1, &id);

	if (!id)
	{
		throw std::runtime_error("couldnt do the texture stuff");
	}

	glBindTexture(GL_TEXTURE_2D, id);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	free(data);

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

}

Texture::~Texture()
{
}

int Texture::getId()
{
	return id;
}