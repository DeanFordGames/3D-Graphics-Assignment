#pragma once
#include <glm/glm.hpp>
#include <wavefront/wavefront.h>

#include "Shader.h"
#include "Mesh.h"
#include "RenderTexture.h"

struct GameObject
{
	GameObject(std::string vShader, std::string fShader);
	~GameObject();

private:

	glm::vec3 _position;
	glm::vec3 _rotation;

	Shader* _objShader;
	RenderTexture* _rt;
	Mesh* _objMesh;
};