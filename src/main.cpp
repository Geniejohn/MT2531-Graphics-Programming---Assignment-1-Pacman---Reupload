#include <iostream>
#include "glm/glm/glm.hpp"
#include "logger.h"
#include "gameloop.hpp"
#include "constants.h"
#include "inputManager.hpp"
#include "resourceManager.hpp"
#include "level.hpp"
#include "pacman.hpp"
#include "ghost.hpp"
#include <vector>

ResourceManager resourceManager;		//Loads and constains all texturs as well as handeling most of the OpenGL calls.
InputManager inputManager;				//Sends signals to pacman, UI, and gameloop depending input from user.
GameLoop gameLoop;						//The object that handles everyhing having to do with running the game itself.
Pacman player;								//The player object. Is global since so many systems is dependent on information from pacman.
std::vector<Ghost> ghosts;				//Vector to hold ghosts.


Level level;
float dt;																			//DeltaTime: the time it took to complete the last frame.

int main()
{
	if(resourceManager.startup() != 0)										//Failed to load any of the textures:
	{
		LOG_DEBUG("Failed to run resourceManager startup.");
		return -1;																	//Exit with code -1.
	}

	gameLoop.makeSprites(0);													//Parameter is what level to load.
	LOG_DEBUG("Level created");
	resourceManager.loadShaderAttributes();								//VERY IMPORTANT, NEEDS TO BE THE LAST THING IN SETUP.


	int nbFrames = 0;
	double currentTime = 0;
	double lastTime = glfwGetTime();

	while(true)																		//MainMenu() returns true. Meaning, we are running another game.
	{
																						//We now entered a game.
	    do
	    {																				//Keep running game.
			 																			//Measure speed:
			currentTime = glfwGetTime();
			nbFrames++;
			if (currentTime - lastTime >= 1.0) { 							// If last prinf() was more than 1sec ago
				dt = 1.0 / double(nbFrames);									// printf and reset
				printf("%f dt\n", dt);
				nbFrames = 0;
				lastTime += 1.0;
			}
			gameLoop.run();														//The gamloop updates and draws everything game realated.

		} while(gameLoop.getRunning());										//Exit out of game if press esc or collect all pellets.

		 //Show game over menu().

	}

	resourceManager.shutdown();												//Time to close the window.

    return (0);
}


//Code XL / G-debug. (gDEBugger)
