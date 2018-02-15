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
#include "spriteAnimated.hpp"
#include "constants.h"


class GameLoop
{
    private:
      bool running;			//True as long as game is running.

	  Sprite* sprite;		//test sprite.
	  Sprite* sprite2;

    public:
        GameLoop()
		{
			running = true;
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
