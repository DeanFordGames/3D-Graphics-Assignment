#include "GameObject.h"

GameObject::GameObject()
{
	_position = glm::vec3(0.0f, 0.0f, 0.0f);
	_model = { 0 };
	_model_matrix = { 1.0f };
	_angle = 0.0f;
	_proj_matrix = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 200.0f);

	_shader = new Shader("shaders/lightVShaderSrc.txt", "shaders/lightFShaderSrc.txt");

	_model_loc = glGetUniformLocation(_shader->getId(), "u_Model");
	_proj_loc = glGetUniformLocation(_shader->getId(), "u_Projection");
}

void GameObject::SetModel(const char* filePath)
{
	if (WfModelLoad(filePath, &_model) != 0)
	{
		throw std::runtime_error("model not load");
	}
}

void GameObject::Draw()
{
	_shader->use();

	_model_matrix = { 1.0f };
	_model_matrix = glm::translate(_model_matrix, _position);
	_model_matrix = glm::rotate(_model_matrix, glm::radians(_angle), glm::vec3(0, 1.0f, 0));


	glUniformMatrix4fv(_model_loc, 1, GL_FALSE, glm::value_ptr(_model_matrix));
	glUniformMatrix4fv(_proj_loc, 1, GL_FALSE, glm::value_ptr(_proj_matrix));

	glBindVertexArray(GetModel().vaoId);
	glBindTexture(GL_TEXTURE_2D, GetModel().textureId);
	glDrawArrays(GL_TRIANGLES, 0, GetModel().vertexCount);


	glBindVertexArray(0);
	glUseProgram(0);
}
