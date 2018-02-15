#pragma once
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;
const int GHOST_AMOUNT = 4;
const int STARTING_LIVES = 3;
const int SCORE_PELLET = 10;

const float HORIZONTAL_GAMESPACE = 0.7f;		//Proportion of window containing the game.
const float VERTICAL_GAMESPACE = 0.7f;			//Proportion of window containing the game.
const float CENTER_TOLERANCE = 0.15f;			//Tolereance for character snap to center.
//Speed in tiles per second.
const float GHOST_SPEED = 2.8f;
const float PACMAN_SPEED = 2.5f;

enum Texture : int									//The different textrues a static sprite can have.
{
	test, pacSheet, ghostSheet, empty, pellet, upgrade, wall, 
};

enum Animation									//The different sprite sheet animations in the game.
{
	pacmanAnimation, ghostAnimation,
};

enum Character
{
	pacman, ghost,
};

enum Direction
{
	still, left, up, right, down,

};
const int STARTING_DIRECTION = right;			//Below 'Direction' definition.

const int TEXTURE_COUNT = 3;					//The total number of textures that will be loaded.
//Can not be const:
char FILES[3][50] =								//List of paths to all the files used by the game.
{												//should be automated to read from folder instead in the future.
	"./assets/test.png",
	"./assets/pacman.png",
	"./assets/ghost.png"
};
