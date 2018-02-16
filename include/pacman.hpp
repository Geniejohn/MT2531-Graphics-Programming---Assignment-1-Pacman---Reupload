#pragma once
#include "glm/glm/glm.hpp"

#include "movableCharacter.hpp"
#include "constants.h"

extern Level level;
// extern GAMEUI gameUI;

class Pacman : public MovableCharacter
{
	private:
		int lives;
		int startingTileID;										//ID of tile Pacman spawns at.

	public:

		Pacman() = default;


		Pacman& operator =(const Pacman& other) = default;

		//MovableCharacter(int Id, int x, int y)
		//Call base-class constructor:
		Pacman(int Id) : MovableCharacter(Id, test, glm::vec2(PACMAN_SPEED*level.retTSize().x, PACMAN_SPEED*level.retTSize().x))
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


		glm::vec2 retPos()
		{
			return MovableCharacter::pos;
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
			//	gameUI.gameOver();
			}
		}


		//Sets Pacman to back to starting position:
		void respawn()
		{
			MovableCharacter::tileID = startingTileID;
			MovableCharacter::pos = level.getTilePos(startingTileID);
		}
};
