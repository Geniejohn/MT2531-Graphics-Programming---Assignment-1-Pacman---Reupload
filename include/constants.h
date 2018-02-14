#pragma once
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;
const int TEXTURE_COUNT = 1;		//The total number of textures that will be loaded.
const int GHOST_AMOUNT = 4;
const float HORIZONTAL_GAMESPACE = 0.7;			//Proportion of window containing the game.
const float VERTICAL_GAMESPACE = 0.7;			//Proportion of window containing the game.


enum Texture
{
	empty, pellet, upgrade,
};

enum Direction
{
	still, left, up, right, down,
};
