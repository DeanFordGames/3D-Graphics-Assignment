#define SDL_MAIN_HANDLED
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <wavefront/wavefront.h>

#include <vector>
#include <iostream>

#include <stdexcept>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

//#define STB_IMAGE_IMPLEMENTATION
#include <glm/stb_image.h>

#include "Window.h"
#include "Texture.h"
#include "Shader.h"
#include "RenderTexture.h"
#include "Mesh.h"


int main()
{
	//create window stuff
	Window window;
	//create mesh
	Mesh sm(0);
	//create shaders
	Shader shader("shaders/postprocessVertex.vert", "shaders/FShaderSrc.txt");
	Shader lshader("shaders/lightVShaderSrc.txt", "shaders/lightFShaderSrc.txt");
	Shader thesholdShader("shaders/postprocessVertex.vert", "shaders/thresholdFrag.frag");
	Shader blurShader("shaders/postprocessVertex.vert", "shaders/blurFrag.frag");
	Shader mergeShader("shaders/postprocessVertex.vert", "shaders/mergeFrag.frag");

	RenderTexture rt(200, 200);
	RenderTexture thresholdRT(200, 200);
	RenderTexture blurRT1(200, 200);
	RenderTexture blurRT2(200, 200);
	RenderTexture mergeRT(200, 200);

	bool quit = false;
	float angle = 0.0f;


	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);


	GLint modelLoc = glGetUniformLocation(lshader.getId(), "u_Model");
	GLint projectionLoc = glGetUniformLocation(lshader.getId(), "u_Projection");

	WfModel curuthers = { 0 };

	if (WfModelLoad("models/curuthers/curuthers.obj", &curuthers) != 0)
	{
		throw std::runtime_error("model not load");
	}

	while (!quit)
	{
		
		SDL_Event event = { 0 };
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
		}
		
		glm::vec3 pos = glm::vec3(0, 0, -10.0f);

		glm::mat4 model(1.0f);
		model = glm::translate(model, pos);
		model = glm::rotate(model, glm::radians(angle), glm::vec3(0, 50, 0));

		glViewport(0, 0, 200, 200);
		rt.bind();

		glClearColor(0.5f, 0, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		glEnable(GL_DEPTH_TEST);

		lshader.use();

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glBindVertexArray(curuthers.vaoId);
		glBindTexture(GL_TEXTURE_2D, curuthers.textureId);
		glDrawArrays(GL_TRIANGLES, 0, curuthers.vertexCount);


		glBindVertexArray(0);
		glUseProgram(0);

		glDisable(GL_DEPTH_TEST);

		rt.unbind();

		////////////////////////////////////////////////////

		thresholdRT.bind();

		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		thesholdShader.use();

		glBindVertexArray(sm.getId());
		glBindTexture(GL_TEXTURE_2D, rt.getTexture());
		glDrawArrays(GL_TRIANGLES, 0, sm.vert_Count());


		glBindVertexArray(0);
		glUseProgram(0);

		thresholdRT.unbind();

		///////////////////////////////////////////////////

		blurRT1.bind();

		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		blurShader.use();

		glBindVertexArray(sm.getId());
		glBindTexture(GL_TEXTURE_2D, thresholdRT.getTexture());
		glDrawArrays(GL_TRIANGLES, 0, sm.vert_Count());

		glBindVertexArray(0);
		glUseProgram(0);

		blurRT1.unbind();

		int blurIntense = 10;

		for (int i = 0; i < blurIntense; i++)
		{
			blurRT2.bind();

			glClearColor(0, 0, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			blurShader.use();

			glBindVertexArray(sm.getId());
			glBindTexture(GL_TEXTURE_2D, blurRT1.getTexture());
			glDrawArrays(GL_TRIANGLES, 0, sm.vert_Count());

			glBindVertexArray(0);
			glUseProgram(0);

			blurRT2.unbind();

			///////////////////////////

			blurRT1.bind();

			glClearColor(0, 0, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			blurShader.use();

			glBindVertexArray(sm.getId());
			glBindTexture(GL_TEXTURE_2D, blurRT2.getTexture());
			glDrawArrays(GL_TRIANGLES, 0, sm.vert_Count());

			glBindVertexArray(0);
			glUseProgram(0);

			blurRT1.unbind();
		}

		///////////////////////////////////////////////////

		mergeRT.bind();

		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		mergeShader.use();

		GLint tex1loc = glGetUniformLocation(mergeShader.getId(), "u_Texture1");
		glUniform1i(tex1loc, 1);

		glBindVertexArray(sm.getId());
		glBindTexture(GL_TEXTURE_2D, blurRT1.getTexture());
		glActiveTexture(GL_TEXTURE0 + 1);
		glBindTexture(GL_TEXTURE_2D, rt.getTexture());
		glActiveTexture(GL_TEXTURE0);
		glDrawArrays(GL_TRIANGLES, 0, sm.vert_Count());

		glBindVertexArray(0);
		glUseProgram(0);

		mergeRT.unbind();
		glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

		///////////////////////////////////////////////////


		glClearColor(0, 0, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.use();

		glBindVertexArray(sm.getId());
		glBindTexture(GL_TEXTURE_2D, mergeRT.getTexture());
		glDrawArrays(GL_TRIANGLES, 0, sm.vert_Count());
		

		glBindVertexArray(0);
		glUseProgram(0);

		window.Swap();

	}

	window.~Window();



	return 0;
}