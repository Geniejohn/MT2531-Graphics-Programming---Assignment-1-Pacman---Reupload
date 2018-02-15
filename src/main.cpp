#include <iostream>
#include "glm/glm/glm.hpp"
#include "logger.h"
#include "gameloop.hpp"
#include "constants.h"
#include "resourceManager.hpp"

#define LOG_NO_DEBUG 1															//Determines wether logger.h compiles.

ResourceManager resourceManager;
GameLoop gameLoop;
float dt;																		//DeltaTime: the time it took to complete the last frame.

int main()
{

	if(resourceManager.startup() != 0)											//Failed to load any of the textures:
	{
		LOG_DEBUG("Failed to run resourceManager startup.");
		return -1;																//Exit with code -1.
	}

	gameLoop.makeSprites();
	resourceManager.loadShaderAttributes();										//VERY IMPORTANT, NEEDS TO BE THE LAST THING IN SETUP.


	int nbFrames = 0;
	double lastTime = glfwGetTime();



    do
    {
																				//Measure speed:
		double currentTime = glfwGetTime();
		if (currentTime - lastTime >= 1.0)  									//If last prinf() was more than 1sec ago
		{
			double temp =  1000.0 / double(nbFrames);										//Printf and reset
			dt = float(temp);
			LOG_DEBUG("dt: %f",dt);
			nbFrames = 0;
			lastTime += 1.0;
		}


        gameLoop.run();

    }while(gameLoop.getRunning());

	resourceManager.shutdown();

    return (0);
}


//Code XL / G-debug. (gDEBugger)
