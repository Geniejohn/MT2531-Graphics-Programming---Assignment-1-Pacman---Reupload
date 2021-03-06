#pragma once
#include "glm/glm/glm.hpp"

//#include "spriteAnimated.hpp"
#include "constants.h"
#include "level.hpp"
#include "pacman.hpp"
#include "inputManager.hpp"
#include "ghost.hpp"
#include "gameUI.hpp"
#include <vector>

extern Level level;
extern InputManager inputManager;
extern Pacman player;
extern std::vector<Ghost> ghosts;


class GameLoop
{
    private:
      bool running;			//True as long as game is running.
	  GameUI gameUI;

    public:
        GameLoop()
		{
			running = true;
		}


		~GameLoop()
		{

		}


		void makeSprites(int levelToLoad)
		{
			level = Level(levelToLoad);
			player = Pacman(level.retStartTileID());			//Start-tile to read from level-file.

			std::vector<int> tempV = level.retGhostVector();	//Get vector with tile-ID's for ghosts.
			for (int i = 0; i < tempV.size(); i++)				//For each ghost read from level-file.
			{
				ghosts.push_back(tempV[i]);						//Add ghost to vector.
			}

			gameUI.startup();
		}


        void run()
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			inputManager.update();
			player.update();
			for (int i = 0; i < ghosts.size(); i++)				//For each ghost.
			{
				ghosts[i].update();								//Call update-function for that ghost.
			}

			level.draw();
			player.draw();
			for (int i = 0; i < ghosts.size(); i++)				//For each ghost.
			{
				ghosts[i].draw();								//Call draw-function for that ghost.
			}
			gameUI.draw();

			glfwSwapBuffers(resourceManager.window);
			glfwPollEvents();

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
			 LOG_DEBUG("ENDLOOP!");
		}

};
