#include "logger.h"
#include "gameloop.hpp"
#include <iostream>

GameLoop gameLoop;

int main(void)
{
	std::cout << "\nMain started.";
	//Static code.

    if (gameLoop.startup() != 0)
    {
		// LOGGER_DEBUG
        return -1;
    }
	std::cout << "\nMain startup done.";


    do
    {
		std::cout << "\nGameLoop";

        gameLoop.run();

    }while(gameLoop.getRunning());


	std::cout << "\nMain exiting(0)\n";
    return (0);
}
