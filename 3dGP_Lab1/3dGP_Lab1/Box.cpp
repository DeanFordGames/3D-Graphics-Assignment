#include "Box.h"


Box::Box()
{
	// spawn the  boxes with a random x value
	float randX = rand() % 20 - 10.0f;

	glm::vec3 pos = glm::vec3(randX, -2.0f, -50.0f);

	SetPosition(pos);
}

void Box::Update()
{
	//moves boxes up the scene
	glm::vec3 changePos = glm::vec3(0.0f, 0.0f, 0.1f);

	UpdatePosition(changePos);
}