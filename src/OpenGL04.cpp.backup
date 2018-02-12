#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <time.h>
#include <cstdlib>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"
#include "glm/glm/gtc/type_ptr.hpp"
#include "SOIL.h"
#include "shaderload.h"
#include <iomanip>


using namespace glm;

GLuint shaderProgram;
const float ANIMATION_SPEED = 0.0004f;		//Updates twice per second.
const int 	ANIMATION_FRAME_COUNT = 13;	//Which means hightest index is 12.
const int 	ANIMATION_LOOPSTART_FRAME = 5;//On which frame does the animation start looping, 0 if none.
const int 	ANIMATION_ROWS = 4;
const int 	ANIMATION_COLUMNS = 4;



const float FRAME_DELAY = 1000;


float g_timeLeft = FRAME_DELAY;
int g_currentFrame = 0;



// Gets the index of a frame and returns that frames coordinates on the spritesheet.
// Function assumes that the first frame on sheet has index 0.
// Returns a pointer to a float array with u1, v1, u2, v2.
float* returnUVCoordsFromFrameNumber (int frameNumber, int uDivisions, int vDivisions)
{
    float uD = uDivisions;                                      // Saves as float for division
    float vD = vDivisions;                                      // calculation.
    float uSize = 1/uD;                                         // Size of one sprite in sheet.
    float vSize = 1/vD;

    float uCoord2 = ((frameNumber % uDivisions)+1)/uD;          // Modulo to not care about row nr.
    float uCoord1 = uCoord2 - uSize;                            // u1 is uSize away from u2.

    float vCoord2 = (std::ceil((frameNumber+1)/uD))/vD;         // Divide by uD to not care about
    float vCoord1 = vCoord2 - vSize;                            // Column nr.

    float coords[4] = {uCoord1, vCoord1, uCoord2, vCoord2};
    float *p = new float[4];
    p = coords;
    return (p);
}



void static_code(GLuint &vao, GLuint &vbo, GLuint &ebo, GLuint(&textures)[2]) {

	glBindVertexArray(vao);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);


	glGenBuffers(1, &vbo);

	shaderProgram = create_program("vertex.vert", "fragment.frag");

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 7 * 4, NULL, GL_DYNAMIC_DRAW);
	

	glGenBuffers(1, &ebo);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*3*2, NULL, GL_DYNAMIC_DRAW);

	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), 0);

	GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));

	GLint texAttrib = glGetAttribLocation(shaderProgram, "texcoord");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat)));



	// Load textures

	glGenTextures(2, textures);

	int width, height;
	unsigned char* image;
	float x, y, widthT, heightT;

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	image = SOIL_load_image("./resources/spritesheet.png", &width, &height, 0, SOIL_LOAD_AUTO);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);


	glUniform1i(glGetUniformLocation(shaderProgram, "texOne"), 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);






	glActiveTexture(GL_TEXTURE1);

	//Sample code for loading additional sprite. But not used in this code
	glBindTexture(GL_TEXTURE_2D, textures[1]);

	image = SOIL_load_image("./resources/spritesheet.png", &width, &height, 0, SOIL_LOAD_AUTO);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glUniform1i(glGetUniformLocation(shaderProgram, "texTwo"), 1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

}



void dynamic_code(GLuint &vao, GLuint &vbo, GLuint &ebo, GLuint(&textures)[2])
{
	// Use a Vertex Array Object
	glBindVertexArray(vao);
	glActiveTexture(GL_TEXTURE1);

	
	float* UV = returnUVCoordsFromFrameNumber(g_currentFrame-1, ANIMATION_COLUMNS, ANIMATION_ROWS);

	GLfloat vertices[] = {

		0.5f, 	1.0f,		1.0f,	1.0f, 	1.0f,		UV[0], 	UV[1], 	// Left 	Top
		1.0f, 	1.0f,		1.0f,	1.0f, 	1.0f,		UV[2], 	UV[1], 	// Right 	Top
		0.5f, 	0.5f, 		1.0f,	1.0f, 	1.0f,		UV[0], 	UV[3],	// Left 	Bottom
		1.0f, 	0.5f, 		1.0f,	1.0f, 	1.0f,		UV[2], 	UV[3] 	// Right 	Bottom
	};//X 		Y 			R 		G 		B			U 		V

	glBindVertexArray(vao);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	




	GLuint elements[] = {
		0, 1, 2,
		2, 3, 0

	};

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(elements), elements);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const GLvoid*)0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


int main(void)
{
	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return -1;
	}
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	GLFWwindow* window = glfwCreateWindow(1024, 768, "OpenGL04", NULL, NULL);
	glfwMakeContextCurrent(window);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window.\n");
		getchar();
		glfwTerminate();
		return -1;
	}
	glewExperimental = GL_TRUE;
	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}


	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSwapInterval(1);
	GLuint vao;
	GLuint vbo;
	GLuint ebo;
	GLuint textures[2];
	
	// Set OpenGL options

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	static_code(vao,vbo, ebo, textures);
	glClearColor(1,1,1,1);
	double lastTime = glfwGetTime();
	int nbFrames = 0;

	do {
	
		// Measure speed
		double currentTime = glfwGetTime();
		nbFrames++;
		if (currentTime - lastTime >= 1.0) { // If last prinf() was more than 1sec ago
											 // printf and reset
			printf("%f ms/frame\n", 1000.0 / double(nbFrames));
			nbFrames = 0;
			lastTime += 1.0;
		}

		g_timeLeft -= 1;
		if(g_timeLeft < 0){					//If time to switch frame:.

			g_currentFrame++;				//Increment frame count.
			if(g_currentFrame == ANIMATION_FRAME_COUNT){
				g_currentFrame = ANIMATION_LOOPSTART_FRAME -1;
			}	
			g_timeLeft = FRAME_DELAY;		//Reset countdown.
		}



		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
		dynamic_code(vao, vbo, ebo, textures);

		glfwSwapBuffers(window);
		glfwPollEvents();

	} 
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);
	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;
}
