#pragma once
#include <cstdlib>
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
#include "constants.h"

extern bool firstSprite;

class Sprite
{
	private:
		GLuint vao;																//Vertex array with the 4 verticies.
		GLuint vbo;																//Vertex buffer object for the 4 vertecies.
		GLuint ebo;																//Element buffer that connects the 4 vertecies into 2 triangles.
		GLuint* shaderProgram;											//ShaderProgram loaded once, shared between all sprites.
		GLuint* textures[TEXTURE_COUNT];									//Holds the textures for all possible sprites in the game.

        //
		// char* loadTextureFromFile(char* path, int no)
		// {
        //
		// 	glGenTextures(2, textures);
        //
		// 	int width, height;
		// 	unsigned char* image;
		// 	float x, y, widthT, heightT;
        //
		// 	glActiveTexture(GL_TEXTURE0 + no);
		// 	glBindTexture(GL_TEXTURE_2D, textures[0]);
		// 	image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_AUTO);
		// 	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		// 	SOIL_free_image_data(image);
        //
        //
		// 	glUniform1i(glGetUniformLocation(shaderProgram, "texOne"), 0);
        //
		// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// }

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

	public:
		Sprite(glm::vec2 worldPos, glm::vec2 size, glm::vec4 uv, Texture textureIndex)	//Constructs the sprite at given pos, with size, uv and texture.
		{
			LOG_DEBUG("sprite constructor started.");
																		//UV is vec4(startU, startV, endU, endV).
			glBindVertexArray(vao);

			LOG_DEBUG("VAO 1.");

			glGenVertexArrays(1, &vao);

			LOG_DEBUG("VAO 2.");

			glBindVertexArray(vao);

			LOG_DEBUG("VAO 3.");


			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 7 * 4, NULL, GL_DYNAMIC_DRAW);

			LOG_DEBUG("VBO created.");

			glGenBuffers(1, &ebo);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*3*2, NULL, GL_DYNAMIC_DRAW);

			LOG_DEBUG("EBO created.");


			if(firstSprite)														//If first sprite to be made:
			{
				LOG_DEBUG("Creating shaderProgram.");
				shaderProgram = new GLuint;
				*shaderProgram = create_program("vertex.vert", "fragment.frag");
			}

			GLint posAttrib = glGetAttribLocation(*shaderProgram, "position");
			glEnableVertexAttribArray(posAttrib);
			glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), 0);

			GLint colAttrib = glGetAttribLocation(*shaderProgram, "color");
			glEnableVertexAttribArray(colAttrib);
			glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));

			GLint texAttrib = glGetAttribLocation(*shaderProgram, "texcoord");
			glEnableVertexAttribArray(texAttrib);
			glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat)));

			if(firstSprite)														//If first sprite to be made:
			{
				//for (int i = 0; i < TEXTURE_COUNT; i++)
				//{
					textures[0] = new GLuint;
			//	}
				glGenTextures(1, *textures);

				int width, height;
				unsigned char* image;
				float x, y, widthT, heightT;

				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, *textures[0]);
				image = SOIL_load_image("./assets/test.png", &width, &height, 0, SOIL_LOAD_AUTO);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
				SOIL_free_image_data(image);


				glUniform1i(glGetUniformLocation(*shaderProgram, "texOne"), 0);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			}


			firstSprite = false;												//First sprite has been made. The rest will not load resources.
		}


		~Sprite()
		{
			//Delete shader program.
		}


		void draw()
		{
			// Use a Vertex Array Object
			glBindVertexArray(vao);
			glActiveTexture(GL_TEXTURE1);


			// float* UV = returnUVCoordsFromFrameNumber(0, ANIMATION_COLUMNS, ANIMATION_ROWS);

			// GLfloat vertices[] = {
            //
			// 	0.5f, 	1.0f,		1.0f,	1.0f, 	1.0f,		UV[0], 	UV[1], 	// Left 	Top
			// 	1.0f, 	1.0f,		1.0f,	1.0f, 	1.0f,		UV[2], 	UV[1], 	// Right 	Top
			// 	0.5f, 	0.5f, 		1.0f,	1.0f, 	1.0f,		UV[0], 	UV[3],	// Left 	Bottom
			// 	1.0f, 	0.5f, 		1.0f,	1.0f, 	1.0f,		UV[2], 	UV[3] 	// Right 	Bottom
			// };//X 		Y 			R 		G 		B			U 		V

			GLfloat vertices[] = {

				0.5f, 	1.0f,		1.0f,	1.0f, 	1.0f,		0, 		0, 	// Left 	Top
				1.0f, 	1.0f,		1.0f,	1.0f, 	1.0f,		1.0f,  	0, 	// Right 	Top
				0.5f, 	0.5f, 		1.0f,	1.0f, 	1.0f,		0, 		1.0f,	// Left 	Bottom
				1.0f, 	0.5f, 		1.0f,	1.0f, 	1.0f,		1.0f, 	1.0f 	// Right 	Bottom
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

};
