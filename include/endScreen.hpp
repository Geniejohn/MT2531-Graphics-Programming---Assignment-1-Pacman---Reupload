#pragma once
#include "sprite.hpp"
#include "counter.hpp"

class EndScreen
{
	private:
		Sprite score;
		Sprite time;
		Sprite gameOverSprite;
		Sprite victorySprite;
		Sprite pressAny;						//'Press any key to return to main menu'.
		Counter scoreCounter;


		//Takes ints and returns position.
		//E.G. fracX =
		glm::vec2 retWPos(int fracX, int fracY)
		{

		}

	public:

		void startup()
		{
			gameOverSprite = new Sprite();
			scoreCounter = Counter(glm::vec2(0, 0.7f), glm::vec2(33,30));
		}


		void draw()
		{
			scoreCounter.draw();
			//Draw lives
			//Draw cherrys
		}
};
