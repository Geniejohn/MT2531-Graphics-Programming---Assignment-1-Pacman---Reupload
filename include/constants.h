#pragma once
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;
const int TEXTURE_COUNT = 2;					//The total number of textures that will be loaded.
const float HORIZONTAL_GAMESPACE = 0.7;			//Proportion of window containing the game.
const float VERTICAL_GAMESPACE = 0.7;			//Proportion of window containing the game.


enum Texture
{
	test, empty, pellet, upgrade,
};

enum Direction
{
	left, up, right, down,
};

//Can not be const.
char FILES[2][50] =								//List of paths to all the files used by the game.
{												//should be automated to read from folder instead in the future.
	"./assets/test.png",
	"./assets/pacman.png"
};
