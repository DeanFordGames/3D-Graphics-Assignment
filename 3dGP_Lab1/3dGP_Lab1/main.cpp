#define SDL_MAIN_HANDLED
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

//#include <wavefront/wavefront.h>

#include <vector>
#include <iostream>

#include <stdexcept>

//#define STB_IMAGE_IMPLEMENTATION
#include <glm/stb_image.h>

#include "Window.h"
#include "RenderTexture.h"
#include "Box.h"
#include "GameObject.h"
#include "Player.h"
#include "Camera.h"
#include "Mesh.h"


int main()
{
	int rtW = 250;

	//create window stuff
	Window window;
	//create mesh
	Mesh sm(0);
	//create shaders
	Shader shader("shaders/postprocessVertex.vert", "shaders/FShaderSrc.txt");
	Shader thesholdShader("shaders/postprocessVertex.vert", "shaders/thresholdFrag.frag");
	Shader blurShader("shaders/postprocessVertex.vert", "shaders/blurFrag.frag");
	Shader mergeShader("shaders/postprocessVertex.vert", "shaders/mergeFrag.frag");
	//create render textures
	RenderTexture rt(rtW, rtW);
	RenderTexture thresholdRT(rtW, rtW);
	RenderTexture blurRT1(rtW, rtW);
	RenderTexture blurRT2(rtW, rtW);
	RenderTexture mergeRT(rtW, rtW);

	//create camera and game objects being used
	Camera cam = Camera();

	std::vector<Box*> boxes;
	boxes.push_back(new Box());
	boxes.back()->SetModel("models/curuthers/curuthers.obj");


	Player player = Player();
	player.SetPosition(glm::vec3(0, -4.5f, -15.0f));
	player.SetModel("models/croc/Babycrocodile.obj");
	player.SetAngle(90.0f);


	GameObject floor = GameObject();
	floor.SetModel("models/floor/floor.obj");
	floor.SetPosition(glm::vec3(0.0f, -6.0f, -60.0f));
	floor.SetAngle(0.0f);

	// to break the loop when the window is closed
	bool quit = false;
	//for timer
	double oldTime = clock();
	double spawnTimer = 700.0;

	while (!quit)
	{
		double deltaTime = clock() - oldTime;
		oldTime = clock();

		//handles the inputs for the player and window
		SDL_Event event = { 0 };
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_LEFT)
				{
					player.SetLeft(true);
				}
				if (event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_RIGHT)
				{
					player.SetRight(true);
				}
				if (event.key.keysym.sym == SDLK_r)
				{
					player.SetDead(false);
				}
			}else if (event.type == SDL_KEYUP)
			{
				if (event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_LEFT)
				{
					player.SetLeft(false);
				}
				if (event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_RIGHT)
				{
					player.SetRight(false);
				}
			}
		}
		
		//change view port to match render texture
		glViewport(0, 0, rtW, rtW);
		rt.bind();
		//clear buffer and change color
		glClearColor(0.4f, 0.4f, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		glEnable(GL_DEPTH_TEST);

		///
		//if player object gets hit it wont be drawn (its dead)
		if (player.GetDead() == false)
		{
			player.Update(boxes);
			player.Draw(cam.GetProjMatrix(), cam.GetViewMatrix());
		}
		cam.Update(&player, &window);

		floor.Draw(cam.GetProjMatrix(), cam.GetViewMatrix());

		///
		//spawn next box object when needed
		if (spawnTimer <= 0.0)
		{
			if (boxes.size() < 5)
			{
				boxes.push_back(new Box());
				boxes.back()->SetModel("models/curuthers/curuthers.obj");
				spawnTimer = 500.0;
			}
		}
		else
		{
			spawnTimer -= deltaTime;
		}
		//updates all boxes and checks if they are out of bounds
		for (int i = 0; i < boxes.size(); i++)
		{
			boxes[i]->Update();

			if (boxes[i]->GetPositionZ() >= -10.0f)
			{
				delete boxes[i];
				boxes.erase(boxes.begin() + i);
			}

			boxes[i]->Draw(cam.GetProjMatrix(), cam.GetViewMatrix());
		}

		///


		glDisable(GL_DEPTH_TEST);

		rt.unbind();

		////////////////////////////////////////////////////

		thresholdRT.bind();
		//applying first shader to scene
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
		//applying blur to scene for bloom
		int blurIntense = 25;

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
		//merging both blurred scene and original
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


		glViewport(0, 0, cam.GetWindowWidth(), cam.GetWindowHeight());

		///////////////////////////////////////////////////


		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.use();
		//draws the scene onto a canvas mesh
		glBindVertexArray(sm.getId());
		glBindTexture(GL_TEXTURE_2D, mergeRT.getTexture());
		glDrawArrays(GL_TRIANGLES, 0, sm.vert_Count());
		

		glBindVertexArray(0);
		glUseProgram(0);
		//display
		window.Swap();

	}

	window.~Window();


	return 0;
}
