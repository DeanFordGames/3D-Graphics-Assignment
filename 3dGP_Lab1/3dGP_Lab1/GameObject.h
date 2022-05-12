#pragma once
#include <glm/glm.hpp>


struct GameObject
{
	GameObject();
	~GameObject();

private:

	glm::vec3 _position;
};