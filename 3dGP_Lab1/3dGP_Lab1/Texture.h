#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <stdexcept>
#include <glm/stb_image.h>


struct Texture
{
	Texture(const char* fileName);
	~Texture();

	int getId();

private:

	GLuint id;
};