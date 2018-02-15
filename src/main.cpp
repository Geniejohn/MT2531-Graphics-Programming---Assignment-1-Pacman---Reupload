#include <iostream>
#include "glm/glm/glm.hpp"
#include "logger.h"
#include "gameloop.hpp"
#include "constants.h"
#include "resourceManager.hpp"
#include "level.hpp"

//#define LOG_NO_DEBUG 1															//Determines wether logger.h compiles.

ResourceManager resourceManager;
GameLoop gameLoop;
Level level;

int main(void)
{
	if(resourceManager.startup() != 0)											//Failed to load any of the textures:
	{
		LOG_DEBUG("Failed to run resourceManager startup.");
		return -1;																//Exit with code -1.
	}

	gameLoop.makeSprites();
	level = Level(0);
	LOG_DEBUG("Level created");
	resourceManager.loadShaderAttributes();										//VERY IMPORTANT, NEEDS TO BE THE LAST THING IN SETUP.

    do
    {
        gameLoop.run();

    } while(gameLoop.getRunning());

	resourceManager.shutdown();

    return (0);
}


//Code XL / G-debug. (gDEBugger)
