#include "MovableCharacter"
#include "constants.h"
#include <cstdlib>												//rand()
#include "glm/glm/glm.hpp"
#include "cmath"												// abs()
#include "logger.h"

extern Level level;
extern Pacman pacman;

class Ghost : public MovableCharacter
{
	private:

	public:
		//MovableCharacter(int Id, int x, int y)
		//Call base-class constructor:
		Ghost(int Id) : MovableCharacter(Id, ghost, GHOST_SPEED*level.retTSize())
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
			if((abs(diff[0])-abs(diff[1])) > 0.0f)				//Diff on y-axis is smallets.
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
			else												//Closest to Pacman on x-axis.
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
				choice = MovableCharacter::cycleDir(choice, 1);	//Cycle choice direction clockwise.
				LOG_DEBUG("Cycling choice in Ghost.");			//Discover if loop is infinite.
			}

			//Choice should now lead to traversable tile.
			return choice;
		}


		//Return a vector equal to the difference in positon between ghost and pacman:
		glm::vec2 findDirDiff()
		{
			return glm::vec2(MovableCharacter::tPos[0] + pacman.retTilePos()[0],
							 MovableCharacter::tPos[1] + pacman.retTilePos()[1]);													);
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
