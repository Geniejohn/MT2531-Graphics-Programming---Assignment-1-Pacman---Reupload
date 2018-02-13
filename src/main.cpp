#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm/glm.hpp"
#include "logger.h"

Gameloop gameloop;

int main()
{

    do
    {
        
        gameloop.run();

    }while(running);

    return (0);
}