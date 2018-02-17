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

ResourceManager resourceManager;
InputManager inputManager;
GameLoop gameLoop;
Pacman player;
std::vector<Ghost> ghosts;										//Vector to hold ghosts.


Level level;
float dt;																		//DeltaTime: the time it took to complete the last frame.

int main()
{
	if(resourceManager.startup() != 0)											//Failed to load any of the textures:
	{
		LOG_DEBUG("Failed to run resourceManager startup.");
		return -1;																//Exit with code -1.
	}

	level = Level(0);
	gameLoop.makeSprites();
	LOG_DEBUG("Level created");
	resourceManager.loadShaderAttributes();										//VERY IMPORTANT, NEEDS TO BE THE LAST THING IN SETUP.


	int nbFrames = 0;
	double currentTime = 0;
	double lastTime = glfwGetTime();

	while(true)//MainMenu() returns true. Meaning, we are running another game.
	{
	    do
	    {																			//Measure speed:
			currentTime = glfwGetTime();
			nbFrames++;
			if (currentTime - lastTime >= 1.0) { 								// If last prinf() was more than 1sec ago
				dt = 1.0 / double(nbFrames);									// printf and reset
				printf("%f dt\n", dt);
				nbFrames = 0;
				lastTime += 1.0;
			}
			gameLoop.run();														//The gamloop updates and draws everything game realated.

	    } while(gameLoop.getRunning());
	}

	resourceManager.shutdown();

    return (0);
}


//Code XL / G-debug. (gDEBugger)
