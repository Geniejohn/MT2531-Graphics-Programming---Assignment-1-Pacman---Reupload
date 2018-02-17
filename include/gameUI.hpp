#pragma once

#include "logger.h"
#include "glm/glm/glm.hpp"
#include "sprite.hpp"
#include "constants.h"
#include "counter.hpp"

class GameUI
{
	private:

		Counter scoreCounter;
		Sprite lives[MAX_LIVES];
		//Cherry[] not implemented.

	public:

		void startup()
		{
			scoreCounter = Counter(glm::vec2(SCORE_DIGITS * -0.031f, 0.88f), glm::vec2(0.085f,0.085f));

		}

		void increaseScore(int increase)
		{
			scoreCounter.increaseValue(increase);
		}


		void draw()
		{
			scoreCounter.draw();

			for(int i = 0; i < MAX_LIVES; i++)	//Draw all lives icons:
			{

			}

			//Draw cherrys
		}
};
