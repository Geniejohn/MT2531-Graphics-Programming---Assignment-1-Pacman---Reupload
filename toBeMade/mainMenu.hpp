#pragma once

#include "logger.h"
#include "glm/glm/glm.hpp"
#include "sprite.hpp"
#include "constants.h"

class MainMenu
{
	private:
		Sprite background;
		Sprite playButton;
		Sprite quitButton;

		int selected;

	public:

		MainMenu() = default;

		MainMenu& operator =(const Sprite& other) = default;

		MainMenu(Texture background, Texture playButton, Texture quit)
		{

		}
}
