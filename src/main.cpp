#include <iostream>
#include "glm/glm/glm.hpp"
#include "logger.h"
#include "gameloop.hpp"
#include "sprite.hpp"
#include "constants.h"

GameLoop gameLoop;
bool firstSprite = true;					//First sprite loads shaderProgram and textures,
											//the rest just uses static pointers.
int main(void)
{

    if (gameLoop.startup() != 0)
    {
		LOG_DEBUG("Failed to run gameLoop startup.");
        return -1;
    }

    do
    {

        gameLoop.run();

    }while(gameLoop.getRunning());


    return (0);
}
