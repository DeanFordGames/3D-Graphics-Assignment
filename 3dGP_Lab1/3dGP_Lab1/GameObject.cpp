#include "GameObject.h"


GameObject::GameObject()
{
	_position = glm::vec3(0.0f, 0.0f, 0.0f);
	_model = { 0 };
	_model_matrix = { 1.0f };
	_angle = 0.0f;

	_shader = new Shader("shaders/lightVShaderSrc.txt", "shaders/lightFShaderSrc.txt");

	_model_loc = glGetUniformLocation(_shader->getId(), "u_Model");
	_proj_loc = glGetUniformLocation(_shader->getId(), "u_Projection");
	_view_loc = glGetUniformLocation(_shader->getId(), "u_View");
}

void GameObject::SetModel(const char* filePath)
{//loading model to use
	if (WfModelLoad(filePath, &_model) != 0)
	{
		throw std::runtime_error("model not load");
	}
}

void GameObject::Draw(glm::mat4 projMatrix, glm::mat4 viewMatrix)
{
	_shader->use();
	// update matrices and draw model
	_model_matrix = { 1.0f };
	_model_matrix = glm::translate(_model_matrix, _position);
	_model_matrix = glm::rotate(_model_matrix, glm::radians(_angle), glm::vec3(0, 1.0f, 0));


	glUniformMatrix4fv(_model_loc, 1, GL_FALSE, glm::value_ptr(_model_matrix));
	glUniformMatrix4fv(_proj_loc, 1, GL_FALSE, glm::value_ptr(projMatrix));
	glUniformMatrix4fv(_view_loc, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	glBindVertexArray(GetModel().vaoId);
	glBindTexture(GL_TEXTURE_2D, GetModel().textureId);
	glDrawArrays(GL_TRIANGLES, 0, GetModel().vertexCount);


	glBindVertexArray(0);
	glUseProgram(0);
}
