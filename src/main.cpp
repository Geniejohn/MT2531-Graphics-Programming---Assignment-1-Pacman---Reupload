#include "logger.h"
#include "gameloop.hpp"
#include <iostream>

GameLoop gameLoop;

int main(void)
{
	//Static code.

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
