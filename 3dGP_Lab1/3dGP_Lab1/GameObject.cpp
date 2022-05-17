#include "GameObject.h"

GameObject::GameObject()
{
	_position = glm::vec3(0.0f, 0.0f, 0.0f);
	_model = { 0 };
}

void GameObject::SetModel(const char* filePath)
{
	if (WfModelLoad(filePath, &_model) != 0)
	{
		throw std::runtime_error("model not load");
	}
}
