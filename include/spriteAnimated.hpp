#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm/glm.hpp"

#include "resourceManager.hpp"
#include "constants.h"
#include "sprite.hpp"

extern float dt;

class SpriteAnimated : public Sprite
{
	private:

		int frameCount;
		int currentFrame;
		float frameDelay;
		float timeLeft;
		Direction direction;													//What direction is the character faceing.
		int reversed;															//Is used to reverse the order of the animation, is 1 or -1.
		Texture index;

	public:

		SpriteAnimated() = default;

		SpriteAnimated& operator =(const SpriteAnimated& other) = default;

		SpriteAnimated(glm::vec2 worldPos, glm::vec2 animationSize, glm::vec2 sheetSize, int frameCount_, float speed, Texture textureIndex) : Sprite(worldPos, animationSize, textureIndex)
		{
			frameCount = ((textureIndex == ghostSheet) ? 2 : 4);
			currentFrame = 0;
			frameDelay = 1 / ((textureIndex == ghostSheet) ? GHOST_ANIMATION_SPEED : PACMAN_ANIMATION_SPEED);
			timeLeft = frameDelay;
			direction = Direction(STARTING_DIRECTION);
			reversed = 1;
			index = textureIndex;
		}

		~SpriteAnimated()
		{

		}

		// int fixDir(Direction dir)
		// {
		// 	dir = Direction(int(dir) -1);
		// 	return (int(dir)%4)+1;												//Rotates the direction. So 1 becomes 2
		// }																		//2 becomes 3, 3 becomes 4, and 4 becomes 1.
		// 																		//also converts to int.
        //

		float fixDir(Direction dir)												//Rotates the direction. So 1 becomes 2
		{																		//2 becomes 3, 3 becomes 4, and 4 becomes 1.
			switch (dir)														//also converts to int.
			{
				case down:
					return 0;
					break;

				case up:
					return 1;
					break;

				case left:
					return 2;
					break;

				case right:
					return 3;
					break;

				default:
					return 1;
					break;
			}
		}

		void update(glm::vec2 pos_, Direction dir)
		{
			setPosition(pos_);
			direction = dir;

			if (direction)														//If standing still, dont progress animation.
			{
				timeLeft -= dt;																//Update the frame if its time:
			}

			if(timeLeft <= 0)
			{																	//If time to switch frame:
				timeLeft = frameDelay;											//Reset countdown.
				currentFrame += reversed;										//Increment frame count. Or decrement if reversed order.
				if(currentFrame == frameCount-1 || currentFrame == 0)
				{
					reversed *= -1;
				}
			}
		}

		void draw()
		{
			glBindVertexArray(vao);

			glBindTexture(GL_TEXTURE_2D, resourceManager.getTexture(Texture(index)));		//1 Since pacman.png is texture no 1.
			glUniform1i(glGetUniformLocation(resourceManager.shaderProgram, "texOne"), 0);

		 	glm::vec4 UV = Sprite::returnUVCoordsFromFrameNumber(currentFrame, 4, 4);
			//LOG_DEBUG("FrameCount: %d UV: %f, %f, %f, %f", currentFrame, UV.x, UV.y, UV.z, UV.w);
			GLfloat vertices[] = {
				pos.x,			pos.y,			1.0f,	1.0f, 	1.0f,	UV.x, 	UV.y + (0.25f * fixDir(direction)), 	// Left 	Top
				pos.x + size.x, pos.y,			1.0f,	1.0f, 	1.0f,	UV.z, 	UV.y + (0.25f * fixDir(direction)), 	// Right 	Top
				pos.x, 			pos.y - size.y,	1.0f,	1.0f, 	1.0f,	UV.x, 	UV.w + (0.25f * fixDir(direction)),	// Left 	Bottom
				pos.x + size.x, pos.y - size.y, 1.0f,	1.0f, 	1.0f,	UV.z, 	UV.w + (0.25f * fixDir(direction)) 	// Right 	Bottom
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
