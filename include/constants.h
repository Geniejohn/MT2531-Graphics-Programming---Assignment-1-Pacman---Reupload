#pragma once
#include "glm/glm/glm.hpp"


const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;
const glm::vec4 BACKGROUND_COLOR = glm::vec4(0,0,0,0);
const int GHOST_AMOUNT = 4;
const int STARTING_LIVES = 3;
const int MAX_LIVES = STARTING_LIVES +1;
const int SCORE_PELLET = 10;
const int SCORE_DIGITS = 5; 	//99999 is max score if this is 5.

const float HORIZONTAL_GAMESPACE = 0.7f;		//Proportion of window containing the game.
const float VERTICAL_GAMESPACE = 0.9f;			//Proportion of window containing the game.
const float CENTER_TOLERANCE = 0.1f;			//Tolereance for character snap to center.
//Speed in tiles per second.
const float GHOST_SPEED = 4.4f;
const float PACMAN_SPEED = 4.5f;
const float WARP_CD = 0.1f;						//Warp cooldown in seconds.
const float INVINCIBILITY_CD = 1.5f;			//Invincibility cooldown in seconds.
//Frame updates per second.
const float PACMAN_ANIMATION_SPEED = 10;
const float GHOST_ANIMATION_SPEED = 3;


const int TEXTURE_COUNT = 7;					//The total number of textures that will be loaded.
enum Texture : int								//The different textrues a static sprite can have.
{
 	pellet, wall, empty, test, pacSheet, ghostSheet, numbers, upgrade,
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

//Can not be const:
char FILES[7][50] =								//List of paths to all the files used by the game.
{												//should be automated to read from folder instead in the future.
	"./assets/pellet.png",
	"./assets/wall.png",
	"./assets/empty.png",
	"./assets/test.png",
	"./assets/pacman.png",
	"./assets/ghost.png",
	"./assets/numbers.png",
};
