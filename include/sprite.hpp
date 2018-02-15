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

#include "resourceManager.hpp"
#include "constants.h"

extern ResourceManager resourceManager;

// extern GLuint vao;																//Vertex array with the 4 verticies.


class Sprite
{
	private:
		glm::vec2 pos;															//Holds world position.
		glm::vec2 size;															//Holds in-world size of the sprite.
		glm::vec2 origin;
		glm::vec2 sheetPos;														//Holds texture position withing spritesheet.
		Texture index;															//Tell the sprite what texture it's using.


		GLuint vbo;																//Vertex buffer object for the 4 vertecies.
		GLuint ebo;																//Element buffer that connects the 4 vertecies into 2 triangles.


	protected:
		// Gets the index of a frame and returns that frames coordinates on the spritesheet.
		// Function assumes that the first frame on sheet has index 0.
		// Returns a pointer to a float array with u1, v1, u2, v2.
		glm::vec4 returnUVCoordsFromFrameNumber (int frameNumber, int uDivisions, int vDivisions)
		{
			float uD = uDivisions;                                      // Saves as float for division
			float vD = vDivisions;                                      // calculation.
			float uSize = 1/uD;                                         // Size of one sprite in sheet.
			float vSize = 1/vD;

			float uCoord2 = ((frameNumber % uDivisions)+1)/uD;          // Modulo to not care about row nr.
			float uCoord1 = uCoord2 - uSize;                            // u1 is uSize away from u2.

			float vCoord2 = (std::ceil((frameNumber+1)/uD))/vD;         // Divide by uD to not care about
			float vCoord1 = vCoord2 - vSize;                            // Column nr.

			glm::vec4 UVCoords = glm::vec4(uCoord1, vCoord1, uCoord2, vCoord2);
			return UVCoords;
		}


	public:
		Sprite(glm::vec2 worldPos, glm::vec2 spriteSize, Texture textureIndex)	//Constructs the sprite at given pos, with size, uv and texture.
		{
			//LOG_DEBUG("Creating new Sprite, type: %d", textureIndex);
			//LOG_DEBUG("Constructor start: VBO: %d, EBO: %d", vbo, ebo);

			pos = worldPos;
			size = spriteSize;
			index = textureIndex;
			origin = glm::vec2(size.x / 2, size.y / 2);

			GLuint vbo;																//Vertex buffer object for the 4 vertecies.
			GLuint ebo;																//Element buffer that connects the 4 vertecies into 2 triangles.


			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 7 * 4, NULL, GL_DYNAMIC_DRAW);

			glGenBuffers(1, &ebo);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*3*2, NULL, GL_DYNAMIC_DRAW);

			LOG_DEBUG("Constructor end: VBO: %d, EBO: %d", vbo, ebo);

		}

		glm::vec2 getSize()
		{
			return size;
		}

		void setPosition(glm::vec2 pos_)
		{
			pos = glm::vec2(pos_.x - origin.x, pos_.y + origin.y);
		}

		void setOrigin(glm::vec2 origin_)
		{
			origin = origin_;
			setPosition(pos);
		}

		void draw()
		{
			// LOG_DEBUG("Draw start: VBO: %d, EBO: %d", vbo, ebo);

			glBindTexture(GL_TEXTURE_2D, resourceManager.getTexture(index));

		 	glm::vec4 UV = returnUVCoordsFromFrameNumber(0, 1, 1);


			// LOG_DEBUG("Pos: %f, %f - %f, %f", pos.x, pos.y, pos.x + size.x, pos.y + size.y);
			LOG_DEBUG("UV: %f, %f, %f, %f", UV[0], UV[1], UV[2], UV[3]);

			GLfloat vertices[] = {
				pos.x,			pos.y,			1.0f,	1.0f, 	1.0f,	UV[0], 	UV[1], 	// Left 	Top
				pos.x + size.x, pos.y,			1.0f,	1.0f, 	1.0f,	UV[2], 	UV[1], 	// Right 	Top
				pos.x, 			pos.y - size.y,	1.0f,	1.0f, 	1.0f,	UV[0], 	UV[3],	// Left 	Bottom
				pos.x + size.x, pos.y - size.y, 1.0f,	1.0f, 	1.0f,	UV[2], 	UV[3] 	// Right 	Bottom
			};//X 				Y 				R 		G 		B		U 		V

			// LOG_DEBUG("Echo");
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

			// LOG_DEBUG("Foxtrot");


			GLuint elements[] = {
				0, 1, 3,
				3, 2, 0
			};

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(elements), elements);
			// LOG_DEBUG("Golf");

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const GLvoid*)0);
			// LOG_DEBUG("Infra");

			// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			// glBindBuffer(GL_ARRAY_BUFFER, 0);
			//glBindVertexArray(0);
			// LOG_DEBUG("Jimmie");

			// LOG_DEBUG("Draw end: VBO: %d, EBO: %d", vbo, ebo);


		}

};
