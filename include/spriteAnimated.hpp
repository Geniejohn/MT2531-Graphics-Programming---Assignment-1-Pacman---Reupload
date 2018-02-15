#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"
#include "glm/glm/gtc/type_ptr.hpp"

#include "resourceManager.hpp"
#include "constants.h"
#include "sprite.hpp"


class SpriteAnimated : public Sprite
{
	private:

		int frameCount;
		int currentFrame;
		float frameDelay;
		float timeLeft;
		Direction direction;													//What direction is the character faceing.
		int reversed;															//Is used to reverse the order of the animation, is 1 or -1.
		Animation index;

	public:

		SpriteAnimated(glm::vec2 worldPos, glm::vec2 animationSize, Animation animationIndex) : Sprite(worldPos, animationSize, Texture(animationIndex))
		{
			LOG_DEBUG("	\n\n\nFramecount %d, currentFrame: %d, frameDelay: %f, timeLeft: %f, direction: %d, reversed: %d, index: %d",
							frameCount, currentFrame, frameDelay, timeLeft, direction, reversed, index);

			frameCount = ((animationIndex == ghostAnimation) ? 2 : 4);
			currentFrame = 0;
			frameDelay = 1 / ((animationIndex == ghostAnimation) ? GHOST_ANIMATION_SPEED : PACMAN_ANIMATION_SPEED);
			timeLeft = frameDelay;
			direction = Direction(STARTING_DIRECTION);
			reversed = 1;
			index = animationIndex;

			LOG_DEBUG("	\n\n\nFramecount %d, currentFrame: %d, frameDelay: %f, timeLeft: %f, direction: %d, reversed: %d, index: %d",
			 				frameCount, currentFrame, frameDelay, timeLeft, direction, reversed, index);
		}

		~SpriteAnimated()
		{

		}

		void update(Direction dir)
		{
			direction = dir;
																				//Update the frame if its time:
			if(timeLeft < 0)
			{																	//If time to switch frame:
				currentFrame += reversed;										//Increment frame count. Or decrement if reversed order.
				if(currentFrame == frameCount || currentFrame == 0)
				{
					reversed *= -1;
				}
				timeLeft = frameDelay;											//Reset countdown.
			}
		}

		void draw()
		{

			glBindTexture(GL_TEXTURE_2D, resourceManager.getTexture(pacSheet));		//1 Since pacman.png is texture no 1.

		 	glm::vec4 UV = Sprite::returnUVCoordsFromFrameNumber(1, 4, 4);

			LOG_DEBUG("Pos: %f, %f - %f, %f", pos.x, pos.y, pos.x + size.x, pos.y + size.y);


			GLfloat vertices[] = {
				pos.x,			pos.y,			1.0f,	1.0f, 	1.0f,	UV[0], 	UV[1], 	// Left 	Top
				pos.x + size.x, pos.y,			1.0f,	1.0f, 	1.0f,	UV[2], 	UV[1], 	// Right 	Top
				pos.x, 			pos.y - size.y,	1.0f,	1.0f, 	1.0f,	UV[0], 	UV[3],	// Left 	Bottom
				pos.x + size.x, pos.y - size.y, 1.0f,	1.0f, 	1.0f,	UV[2], 	UV[3] 	// Right 	Bottom
			};//X 				Y 				R 		G 		B		U 		V

			LOG_DEBUG("Echo");
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
//
			LOG_DEBUG("Foxtrot");


			GLuint elements[] = {
				0, 1, 3,
				3, 2, 0
			};

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(elements), elements);
			LOG_DEBUG("Golf");

			resourceManager.loadShaderAttributes();

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const GLvoid*)0);
		}

};
