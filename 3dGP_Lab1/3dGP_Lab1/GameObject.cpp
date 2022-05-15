#include "GameObject.h"

GameObject::GameObject(std::string vShader, std::string fShader)
{
	_objShader = new Shader(vShader, fShader);
	_rt = new RenderTexture(200, 200);
	_objMesh = new Mesh(0);

}

GameObject::~GameObject()
{

}