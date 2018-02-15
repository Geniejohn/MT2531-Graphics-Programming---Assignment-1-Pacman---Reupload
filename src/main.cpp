#include <iostream>
#include "glm/glm/glm.hpp"
#include "logger.h"
#include "gameloop.hpp"
#include "constants.h"
#include "resourceManager.hpp"

ResourceManager resourceManager;
GameLoop gameLoop;
GLuint vao;																//Vertex array with the 4 verticies.
GLuint vbo;																//Vertex buffer object for the 4 vertecies.
GLuint ebo;																//Element buffer that connects the 4 vertecies into 2 triangles.

int main(void)
{

    if(gameLoop.startup() != 0)													//Failed to initilize
    {
		LOG_DEBUG("Failed to run gameLoop startup.");
		return -1;																//Exit with code -1.
    }


	//VAO, VBO, EBO startup:
	//UV is vec4(startU, startV, endU, endV).
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 7 * 4, NULL, GL_DYNAMIC_DRAW);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*3*2, NULL, GL_DYNAMIC_DRAW);


	if(resourceManager.startup() != 0)											//Failed to load any of the textures:
	{
		LOG_DEBUG("Failed to run resourceManager startup.");
		return -1;																//Exit with code -1.
	}

    do
    {
        gameLoop.run();

    }while(gameLoop.getRunning());


    return (0);
}


//Code XL / G-debug. (gDEBugger)
