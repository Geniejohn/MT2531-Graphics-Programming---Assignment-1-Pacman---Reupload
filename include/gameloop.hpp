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


	  Sprite* sprite;		//test sprite.
	  Sprite* sprite2;

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
		}


		void makeSprites()
		{

			sprite = new Sprite(
				glm::vec2(-0.5f,	0.5f),										//Position.
				glm::vec2(1,		1),											//Size.
				empty);

			sprite2 = new Sprite(
				glm::vec2(-1,		0),										//Position.
				glm::vec2(1,		1),											//Size.
				test);
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


			sprite-> draw();
			sprite2-> draw();

			glfwSwapBuffers(resourceManager.window);
			glfwPollEvents();

			if(glfwGetKey(resourceManager.window, GLFW_KEY_ESCAPE))								//If user exits:
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
