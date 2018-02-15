#pragma once
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;
const int TEXTURE_COUNT = 2;					//The total number of textures that will be loaded.
const float HORIZONTAL_GAMESPACE = 0.7;			//Proportion of window containing the game.
const float VERTICAL_GAMESPACE = 0.7;			//Proportion of window containing the game.
const int GHOST_AMOUNT = 4;
const float HORIZONTAL_GAMESPACE = 0.0f;			//Proportion of window containing the game.
const float VERTICAL_GAMESPACE = 0.7f;			//Proportion of window containing the game.
const float CENTER_TOLERANCE = 0.25f;			//Tolereance for character snap to center.


enum Texture
{
	test, empty, pellet, upgrade,
};

enum Character
{
	pacman, ghost,
};

enum Direction
{
	still, left, up, right, down,
};

//Can not be const.
char FILES[2][50] =								//List of paths to all the files used by the game.
{												//should be automated to read from folder instead in the future.
	"./assets/test.png",
	"./assets/pacman.png"
};
