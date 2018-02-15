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
//#include "spriteAnimated.hpp"
#include "constants.h"


class GameLoop
{
    private:
      bool running;			//True as long as game is running.

	  Sprite* sprite;		//test sprite.
	  Sprite* sprite2;		//test sprite.

	  //SpriteAnimated* animation;

    public:
        GameLoop()
		{
			running = true;
		}


		~GameLoop()
		{
			delete sprite;
			delete sprite2;
		}


		void makeSprites()
		{
			sprite2 = new Sprite(
				glm::vec2(-0.0f,	0.0f),										//Position.
				glm::vec2(1,		1),											//Size.
				test);
			sprite = new Sprite(
				glm::vec2(-1,	1),										//Position.
				glm::vec2(1,		1),											//Size.
				test);

		// 	animation = new SpriteAnimated(
		// 		glm::vec2(0,		0),										//Position.
		// 		glm::vec2(1,		1),											//Size.
		// 		pacmanAnimation);
		//
		}

        void run()
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//s	animation-> update(right);

			sprite-> draw();
			sprite2-> draw();

			//animation-> draw();

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
