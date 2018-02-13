#include "logger.h"
#include "gameloop.h"


Gameloop gameloop;

int main(void)
{

	//Static code.

    if (startup() != 1)
    {
		// LOGGER_DEBUG
        return -1;
    }


    do
    {
        gameloop.run();

    }while(getRunning());

    return (0);
}
