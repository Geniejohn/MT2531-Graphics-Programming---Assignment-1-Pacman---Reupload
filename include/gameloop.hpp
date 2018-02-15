#pragma once
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <time.h>
#include <cstdlib>

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"
#include "glm/glm/gtc/type_ptr.hpp"

#include "sprite.hpp"
#include "constants.h"


class GameLoop
{
    private:
      bool running;			//True as long as game is running.
      int nbFrames;
      double lastTime;

	  GLFWwindow* window;

	  Sprite* sprite;		//test sprite.
	  Sprite* sprite2;		//test sprite.


    public:
        GameLoop()
		{
		    running = true;
		    nbFrames = 0;
		    lastTime = glfwGetTime();


		}

		~GameLoop()
		{
			delete sprite;

			glfwDestroyWindow(window);
			glfwTerminate();
		}


		// Initialise GLFW window. Returns -1 if failed.
		int startup()
		{

			if (!glfwInit())
			{
				LOG_DEBUG("Failed to initialize GLFW\n");
				getchar();
				return -1;
			}

			glfwWindowHint(GLFW_SAMPLES, 4);
			glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 				// To make MacOS happy; should not be needed
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


			window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Pacman", NULL, NULL);
			glfwMakeContextCurrent(window);
			if (window == NULL) {
				LOG_DEBUG("Failed to open GLFW window.\n");
				getchar();
				glfwTerminate();
				return -1;
			}


			glewExperimental = GL_TRUE;
			// Initialize GLEW
			if (glewInit() != GLEW_OK) {
				LOG_DEBUG("Failed to initialize GLEW\n");
				getchar();
				glfwTerminate();
				return -1;
			}


			glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
			glfwSwapInterval(1);


			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glClearColor(1,1,1,1);


			sprite = new Sprite(
				glm::vec2(-1,	1),										//Position.
				glm::vec2(1,		1),										//Size.
				glm::vec2(1,		1),											//Sprite sheetPosition.
				test);

			sprite2 = new Sprite(
				glm::vec2(-0.6f,	0.6f),										//Position.
				glm::vec2(1,		1),										//Size.
				glm::vec2(1,		1),											//Sprite sheetPosition.
				empty);




			return 0;															//All went well.
		}


        void run()
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		    																	// Measure speed:
		    double currentTime = glfwGetTime();
		    if (currentTime - lastTime >= 1.0) { 								// If last prinf() was more than 1sec ago
		                                            							// printf and reset
		        LOG_DEBUG("%f ms/frame\n", 1000.0 / double(nbFrames));
		        nbFrames = 0;
		        lastTime += 1.0;
		    }

			//dynamic code//
			//sprite->setPosition({-1, 1});

			sprite-> draw();
			//sprite->setPosition({0, 0});
			//sprite->draw();
			sprite2-> draw();

			glfwSwapBuffers(window);
			glfwPollEvents();

			if(glfwGetKey(window, GLFW_KEY_ESCAPE))								//If user exits:
			{
				endLoop();														//End the gameloop.
			}
		}


 		//Retuns false if game should quit.
        bool getRunning()
		{
		    return running;
		}


		//Closes game at end of current loop.
        void endLoop()
		{
		    running = false;
		}

};
