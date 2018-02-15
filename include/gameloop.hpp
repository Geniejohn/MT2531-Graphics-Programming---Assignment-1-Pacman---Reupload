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
#include "level.hpp"

extern Level level;

class GameLoop
{
    private:
      bool running;			//True as long as game is running.


	  //SpriteAnimated* animation;

    public:
        GameLoop()
		{
			running = true;
		}


		~GameLoop()
		{
			
		}


		void makeSprites()
		{

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
			LOG_DEBUG("Will now try to draw level.");
			level.draw();
			LOG_DEBUG("Finished drawing level.");

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
