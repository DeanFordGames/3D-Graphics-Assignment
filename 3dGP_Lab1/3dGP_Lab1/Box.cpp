#include "Box.h"


Box::Box()
{
	float randX = rand() % 10 - 5.0f;

	glm::vec3 pos = glm::vec3(randX, -2.0f, -50.0f);

	SetPosition(pos);
}

void Box::Update()
{
	glm::vec3 changePos = glm::vec3(0.0f, 0.0f, 0.1f);

	UpdatePosition(changePos);
}