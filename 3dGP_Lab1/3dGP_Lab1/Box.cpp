#include "Box.h"

void Box::Update(Player* player)
{
	glm::vec3 changePos = glm::vec3(0.0f, 0.0f, 0.1f);

	UpdatePosition(changePos);

	if (GetPositionZ() >= -10.0f)
	{
		delete this;
	}
	else if (GetPosition() == player->GetPosition())
	{
		delete this;
	}
}