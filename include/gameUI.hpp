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
		//Sprite lives[MAX_LIVES];
		//Cherry[] not implemented.

	public:

		void startup()
		{
			scoreCounter = Counter(glm::vec2(0, 0.7f), glm::vec2(33,30));
		}

		void increaseScore(int increase)
		{
			scoreCounter.increaseValue(increase);
		}


		void draw()
		{
			scoreCounter.draw();
			//Draw lives
			//Draw cherrys
		}
};
