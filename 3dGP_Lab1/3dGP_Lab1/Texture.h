#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>



struct Texture
{
	Texture(const char* fileName);
	~Texture();

	int getId();

private:

	GLuint id;
};