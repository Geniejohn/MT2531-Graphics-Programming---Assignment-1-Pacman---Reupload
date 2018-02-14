#pragma once
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;
const int TEXTURE_COUNT = 1;					//The total number of textures that will be loaded.
const int GHOST_AMOUNT = 4;
const float HORIZONTAL_GAMESPACE = 0.f;			//Proportion of window containing the game.
const float VERTICAL_GAMESPACE = 0.7f;			//Proportion of window containing the game.
const float CENTER_TOLERANCE = 0.25f;			//Tolereance for character snap to center.


enum Texture
{
	empty, pellet, upgrade,
};

enum Direction
{
	still, left, up, right, down,
};
