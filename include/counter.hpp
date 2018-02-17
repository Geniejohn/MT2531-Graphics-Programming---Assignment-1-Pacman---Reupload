#pragma once

#include "logger.h"
#include "glm/glm/glm.hpp"
#include "sprite.hpp"
#include "constants.h"

class Counter
{
	private:
		Sprite digits[SCORE_DIGITS];
		int value;

	public:

		Counter() = default;

		Counter& operator =(const Counter& other) = default;
								//Maybe add new call to resource manager to get the size of the sprite. to skip size param.
		Counter(glm::vec2 pos, glm::vec2 size, int startVal = 0)						//Construct the counter with all its sprites,
		{
			value = startVal;																//and set the value.
			for(int i = 0; i < SCORE_DIGITS; i++)
			{
				digits[i] = Sprite(glm::vec2((i * 0.02f) + pos.x, pos.y), glm::vec2(0.3f, 0.3f), numbers, glm::vec2(10,1), 0);			//40 is spacing between them.
			}
			setValue(value);
		}

		void increaseValue(int incease)
		{
			value += incease;
			setValue(value);
		}

		void setValue(int val)
		{
			LOG_DEBUG("Countor setting value: %d", val);
			int j = 1;

			for(int i = SCORE_DIGITS-1; i > 0; i--)
			{
				j *= 10;
				digits[i].setTextruePosition((val % j) / (j/10));
			}
		}

		void draw()																//Draw all of the spries under the counter.
		{
			for(int i = 0; i < SCORE_DIGITS-1; i++)
			{
				digits[i].draw();
			}
		}
};
