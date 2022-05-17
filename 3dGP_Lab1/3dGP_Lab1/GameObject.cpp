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

void GameObject::Draw(GLint modelLoc, GLint projLoc, glm::mat4 model, glm::mat4 projection)
{
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glBindVertexArray(GetModel().vaoId);
	glBindTexture(GL_TEXTURE_2D, GetModel().textureId);
	glDrawArrays(GL_TRIANGLES, 0, GetModel().vertexCount);


	glBindVertexArray(0);
	glUseProgram(0);
}
