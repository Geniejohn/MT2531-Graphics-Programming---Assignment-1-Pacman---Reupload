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
		Pacman(int Id) : MovableCharacter(Id, pacman, glm::vec2(4,4), 4, PACMAN_ANIMATION_SPEED, pacSheet, glm::vec2(PACMAN_SPEED*level.retTSize().x, PACMAN_SPEED*level.retTSize().x))
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
			LOG_DEBUG("Died!");
			lives--;
			if(lives > 0)										//Not game-over.
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
			LOG_DEBUG("Respawning!");
			MovableCharacter::tileID = startingTileID;
			MovableCharacter::desTPos = level.getTilePos(level.findNextTile(startingTileID, STARTING_DIRECTION));
			MovableCharacter::desiredDir = still;
			MovableCharacter::dir = still;
			MovableCharacter::pos = level.getTilePos(startingTileID);
		}
};
