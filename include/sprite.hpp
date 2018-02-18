#pragma once
#include "resourceManager.hpp"
#include "constants.h"

extern ResourceManager resourceManager;
extern float dt;

// extern GLuint vao;																//Vertex array with the 4 verticies.


class Sprite																	//Is base-class for spriteTexture.
{
	private:
		Texture index;															//Tell the sprite what texture it's using.
		int posInSheet;
		glm::vec2 sheetSize;														//Holds texture position withing spritesheet.
	protected:
		glm::vec2 pos;															//Holds world position.
		glm::vec2 size;															//Holds in-world size of the sprite.
		glm::vec2 origin;

		GLuint vao;																//Vertex array with the 4 verticies.
		GLuint vbo;																//Vertex buffer object for the 4 vertecies.
		GLuint ebo;																//Element buffer that connects the 4 vertecies into 2 triangles.


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

		Sprite() = default;

		Sprite& operator =(const Sprite& other) = default;

		Sprite(	glm::vec2 worldPos, glm::vec2 spriteSize, Texture textureIndex,
			 	glm::vec2 sheetSize_ = glm::vec2(1,1), int texPosInSheet = 0)	//Constructs the sprite at given pos, with size, uv and texture.
		{
			//LOG_DEBUG("Creating new Sprite, type: %d", textureIndex);
			LOG_DEBUG("Constructor start: VBO: %d, EBO: %d", vbo, ebo);
			LOG_DEBUG("posX: %f, posY: %f, sizeX: %f, sizeY: %f, Texture: %d", worldPos.x, worldPos.y, spriteSize.x, spriteSize.y, int(textureIndex));
			pos = worldPos;
			size = spriteSize;
			index = textureIndex;
			//origin = glm::vec2(size.x / 2, size.y / 2);
			posInSheet = texPosInSheet;
			sheetSize = sheetSize_;

			glGenVertexArrays(1, &vao);	//Must come before makeSprites:
			glBindVertexArray(vao);

			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 7 * 4, NULL, GL_DYNAMIC_DRAW);

			glGenBuffers(1, &ebo);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*3*2, NULL, GL_DYNAMIC_DRAW);
			LOG_DEBUG("Constructor end: VBO: %d, EBO: %d", vbo, ebo);

			resourceManager.loadShaderAttributes();
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

		void setTexture(Texture t)
		{
			index = t;
			LOG_DEBUG("Changed Texture!");
		}

		void setTextruePosition(int texPosInSheet)
		{
			if(texPosInSheet > sheetSize.x * sheetSize.y)
			{
				LOG_DEBUG("ERROR: Trying to set position in spritesheet that is bigger than the amount of spirtes in spritesheet.");
			}
			else
			{
				posInSheet = texPosInSheet;
			}
		}

		void draw()
		{
			// LOG_DEBUG("Drawing sprite: pos: %f, %f  -  size: %f, %f  -  Sheetsize: %d, %d  - posInSheet: %d",
			// 			pos.x, pos.y, size.x, size.y, sheetSize.x, sheetSize.y, posInSheet);
			glBindVertexArray(vao);

			glBindTexture(GL_TEXTURE_2D, resourceManager.getTexture(index));
			glUniform1i(glGetUniformLocation(resourceManager.shaderProgram, "texOne"), 0);

		 	glm::vec4 UV = returnUVCoordsFromFrameNumber(posInSheet, sheetSize.x, sheetSize.y);

			GLfloat vertices[] = {
				pos.x,			pos.y,			1.0f,	1.0f, 	1.0f,	UV.x, 	UV.y, 	// Left 	Top
				pos.x + size.x, pos.y,			1.0f,	1.0f, 	1.0f,	UV.z, 	UV.y, 	// Right 	Top
				pos.x, 			pos.y - size.y,	1.0f,	1.0f, 	1.0f,	UV.x, 	UV.w,	// Left 	Bottom
				pos.x + size.x, pos.y - size.y, 1.0f,	1.0f, 	1.0f,	UV.z, 	UV.w 	// Right 	Bottom
			};//X 				Y 				R 		G 		B		U 		V

			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

			GLuint elements[] = {
				0, 1, 3,
				3, 2, 0
			};

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(elements), elements);


			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const GLvoid*)0);

		}

};
