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
			int tempPos = 124;
			player = Pacman(tempPos);												//506 Start on the 0x17th tile.

		// 	animation = new SpriteAnimated(
		// 		glm::vec2(0,		0),										//Position.
		// 		glm::vec2(1,		1),											//Size.
		// 		pacmanAnimation);
		//
		glm::vec2 pac, pacTile, pacLeft, pacUp, pacRight, pacDown;
		pac = player.retPos();
		pacTile = level.getTilePos(tempPos);
		pacLeft = level.getTilePos(tempPos-1);
		pacRight = level.getTilePos(tempPos+1);
		pacUp = level.getTilePos(tempPos-28);
		pacDown = level.getTilePos(tempPos+28);

		LOG_DEBUG("Pacman at pos: %f, %f", pac.x, pac.y);
		LOG_DEBUG("Pacman standing at tile with pos: %f, %f", pacTile.x, pacTile.y);
		LOG_DEBUG("Tile to the left of Pacman at pos: %f, %f", pacLeft.x, pacLeft.y);
		LOG_DEBUG("Tile above Pacman at pos: %f, %f", pacUp.x, pacUp.y);
		LOG_DEBUG("Tile to the right of Pacman at pos: %f, %f", pacRight.x, pacRight.y);
		LOG_DEBUG("Tile below Pacman at pos: %f, %f", pacDown.x, pacDown.y);


		LOG_DEBUG("isTileEmpty(1): %d", level.isTileEmpty(1));

		LOG_DEBUG("isTileEmpty(pacPos): %d", level.isTileEmpty(tempPos));
		LOG_DEBUG("isTileEmpty(left): %d", level.isTileEmpty(tempPos-1));
		LOG_DEBUG("isTileEmpty(right): %d", level.isTileEmpty(tempPos+1));
		LOG_DEBUG("isTileEmpty(up): %d", level.isTileEmpty(tempPos - 28));
		LOG_DEBUG("isTileEmpty(down): %d", level.isTileEmpty(tempPos + 28));



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
