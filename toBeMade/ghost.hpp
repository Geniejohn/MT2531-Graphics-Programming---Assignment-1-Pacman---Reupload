#include "MovableCharacter"
#include "constants.h"
#include <cstdlib>												//rand()
#include "glm/glm/glm.hpp"
#include "cmath"												// abs()
#include "logger.h"

//extern level;
//extern pacman;

class Ghost : MovableCharacter
{
	private:

	public:
		//MovableCharacter(int Id, int x, int y)
		Ghost(int Id) : public MovableCharacter(Id)				//Call base-class constructor:
		{
			lives = STARTING_LIVES;
		}


		~Ghost()
		{

		}


		int makeChoice()
		{
			int choice = 1;										//Default.
			glm::vec2 diff = findDirDiff();						//Try moving towards Pacman first.
			if((abs(diff[0])-abs(diff[1])) < 0.0f)				//Diff on x-axis is smallets.
			{
				if(diff[0] < 0.0f)								//Pacman to the left.
				{
					choice = left;
				}
				else											//Pacman to the right.
				{
					choice = right;
				}
			}
			else												//Closest to Pacman on y-axis.
			{
				if(diff[1] < 0.0f)								//Pacman below.
				{
					choice = down;
				}
				else											//Pacman above.
				{
					choice = up;
				}
			}

			//Next tile in that direction is not traversable:
			while (level.isTileEmpty(level.findNextTile(MovableCharacter::tileID, choice)) == false)
			{
				choice = cycleDir(choice);						//Cycle choice direction.
				LOG_DEBUG("Cycling choice in Ghost.");			//Discover if loop is infinite.
			}

			//Choice should now lead to traversable tile.
			return choice;
		}


		//Takes a direction and returns the next one in the cycle,
		//left->up->right->down-left->up etc:
		int cycleDir(int d)
		{
			return((d%4)+1);
		}


		//Return a vector equal to the difference in positon between ghost and pacman:
		glm::vec2 findDirDiff()
		{
			return glm::vec2(MovableCharacter::tPos[0] + pacman.retTilePos()[0],
							 MovableCharacter::tPos[1] + pacman.retTilePos()[1]);													);
		}


		void update()
		{
			if(MovableCharacter::dir == still)					//Come to a stop.
			{
				MovableCharacter::desiredDir = makeChoice();	//Change direction.
			}
		}
};
