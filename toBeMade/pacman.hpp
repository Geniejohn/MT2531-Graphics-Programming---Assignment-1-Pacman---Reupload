#include "MovableCharacter"
#include "constants.h"
#include "glm/glm/glm.hpp"

extern Level level;
extern GAMEUI gameUI;

class Pacman : public MovableCharacter
{
	private:
		int lives;
		int startingTileID;										//ID of tile Pacman spawns at.

	public:
		//MovableCharacter(int Id, int x, int y)
		//Call base-class constructor:
		Pacman(int Id) : MovableCharacter(Id, pacman, glm::vec2(GHOST_SPEED*level.retTSize()[0], GHOST_SPEED*level.retTSize()[0]))
		{
			startingTileID = Id;
			lives = STARTING_LIVES;
		}


		~Pacman()
		{

		}

		glm::vec2 retTilePos()
		{
			return MovableCharacter::tPos;
		}


		void update()
		{
			MovableCharacter::update();
		}


		//Pacman lose 1 life and possibly triggers a gameover:
		void die()
		{
			lives--;
			if(lives>0)											//Not game-over.
			{
				respawn();
			}
			else												//Game-over.
			{
				gameUI.gameOver();
			}
		}


		//Sets Pacman to back to starting position:
		void respawn()
		{
			MovableCharacter::tileID = startingTileID;
			MovableCharacter::pos = level.retTilePos(startingTileID);
		}
};
