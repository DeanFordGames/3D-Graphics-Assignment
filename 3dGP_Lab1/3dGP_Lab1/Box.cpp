#include "Box.h"

void Box::Update()
{
	glm::vec3 changePos = glm::vec3(0.0f, 0.0f, 0.1f);

	UpdatePosition(changePos);

	if (GetPositionZ() >= -15.0f)
	{
		delete this;
	}
}