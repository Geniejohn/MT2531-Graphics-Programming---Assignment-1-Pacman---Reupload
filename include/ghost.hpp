#pragma once
#include "movableCharacter.hpp"
#include "constants.h"
#include <cstdlib>												//rand()
#include "glm/glm/glm.hpp"
#include "cmath"												// abs()
#include "logger.h"
#include "pacman.hpp"
#include <cstdlib>

extern Level level;
extern Pacman player;

class Ghost : public MovableCharacter
{
	private:

	public:

			Ghost() = default;
			Ghost& operator =(const Ghost& other) = default;

		//MovableCharacter(int Id, int x, int y)
		//Call base-class constructor:
		Ghost(int Id) : MovableCharacter(Id, ghost, glm::vec2(2, 4), 2, GHOST_ANIMATION_SPEED, ghostSheet, glm::vec2(GHOST_SPEED*level.retTSize().x, GHOST_SPEED*level.retTSize().y))
		{

		}


		~Ghost()
		{

		}


		int makeChoice()
		{
			int choice = 1;										//Default.
			glm::vec2 diff = findDirDiff();						//Try moving towards Pacman first.

			//Ghost closer to packman than a tile:
			if(diff.x < level.retTSize().x && diff.y < level.retTSize().y)
			{
				player.die();									//Kill Pacman.
				diff = findDirDiff();							//Get new diff-vector after Pacman-respawn.
				LOG_DEBUG("Killed Pacman!");
			}
			if((abs(diff.x)-abs(diff.y)) > 0.0f)				//Diff on y-axis is smallets.
			{
				if(diff.x < 0.0f)								//Pacman to the left.
				{
					choice = left;
				}
				else											//Pacman to the right.
				{
					choice = right;
				}
			}
			else												//Closest to Pacman on x-axis.
			{
				if(diff.y < 0.0f)								//Pacman below.
				{
					choice = down;
				}
				else											//Pacman above.
				{
					choice = up;
				}
			}

			int randN = (rand()%2);								//Random number, either 0 or 1.

			//1/3rd chance to cycle choice once, 1/9 twice, etc.
			while (rand()%3 == 1)
			{
																//Cycle choice clockwise if randN == 1,
																//Counter-clockwise if randN == 0
				choice = MovableCharacter::cycleDir(choice, randN);
			}

			//Next tile in that direction is not traversable:
			while (level.isTileEmpty(level.findNextTile(MovableCharacter::tileID, choice)) == false)
			{
																//Cycle choice clockwise if randN == 1,
																//Counter-clockwise if randN == 0
				choice = MovableCharacter::cycleDir(choice, randN);
				//LOG_DEBUG("Cycling choice in Ghost.");			//Discover if loop is infinite.
			}

			//Choice should now lead to traversable tile.
			return choice;
		}


		//Return a vector equal to the difference in positon between ghost and pacman:
		glm::vec2 findDirDiff()
		{
			// LOG_DEBUG("Differenc between ghost and pacman: %f, %f", MovableCharacter::tPos.x + player.retTilePos().x, MovableCharacter::tPos.y + player.retTilePos().y);
			return glm::vec2(player.retPos().x - MovableCharacter::pos.x,
							 player.retPos().y - MovableCharacter::pos.y);
		}


		void update()
		{
			//Come to a stop or is able to make 90 degree turn:
			if(MovableCharacter::dir == still || MovableCharacter::canTurn() == true)
			{
				MovableCharacter::desiredDir = makeChoice();	//Change direction.
			}

			MovableCharacter::update();
		}
};
