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
#include "pacman.hpp"
#include "inputManager.hpp"

extern Level level;
extern InputManager inputManager;
extern Pacman player;

class GameLoop
{
    private:
      bool running;			//True as long as game is running.

	  //SpriteAnimated* animation;
	  Sprite sprite;
	  Sprite sprite1;


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
			player = Pacman(506);												//Start on the 0x17th tile.
			sprite = Sprite(
				glm::vec2(-1, 1),
				glm::vec2(1, 1),
				pellet);
			sprite1 = Sprite(
				glm::vec2(0, 0),
				glm::vec2(1, 1),
				empty);

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

			inputManager.update();
			player.update();


			//animation-> draw();
			//LOG_DEBUG("Will now try to draw level.");
			level.draw();
			//LOG_DEBUG("Finished drawing level.");
			player.draw();
			sprite.draw();
			sprite1.draw();


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
