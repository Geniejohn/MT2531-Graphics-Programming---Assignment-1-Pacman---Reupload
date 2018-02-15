#include "sprite.hpp"
#include "logger.h"
#include "level.hpp"
#include "glm/glm/glm.hpp"
#include "spriteAnimated.hpp"
#include "cmath"												// abs()

extern Level level;
extern float dt;												//DeltaTime.
extern GameUI gameUI;

//Base-class for all movable characters:
class MovableCharacter
{
	private:
		int type;												//Enum for character-type.
		glm::vec2 speed;
		SpriteAnimated spriteAnimated;
		bool inTileCenter;

	protected:
		glm::vec2 pos;
		int dir;												//Current movement-direction.
		int desiredDir;											//Desired movement-direction.
		int tileID;												//ID the tile occupied by character.
		glm::vec2 tPos;

	public:
		//Constructor:
		MovableCharacter(int Id, int typ, glm::vec2 s)
		{
			inTileCenter = true;								//Starts in center of tile.
			tileID = Id;
			type = typ;
			speed = s;
			pos = level.getTilePos();
																//Creates new sprite of wanted type:
			spriteAnimated = new SpriteAnimated(pos, level.retTSize(), typ);
			dir = STARTING_DIRECTION;
			desiredDir = STARTING_DIRECTION;
			tPos = level.getTilePos(tileID);					//Sets pos of current tile.
		}


		//Deconstructor:
		~MovableCharacter()
		{
			delete sprite;
		}


		int retType()
		{
			return type;
		}


		glm::vec2 retPos()
		{
			return pos;
		}


		//Change direction:
		void changeDir()
		{
			updateDir();
		}


		//Change the desire direction:
		void changeDesiredDir(int desDir)
		{
			if(desDir < 0 || desDir > 4)						//'d' out of range.
			{
				LOG_DEBUG("Desired direction-argument is out of range(0-3).");
			}
			else												//'d' in range.
			{
				updateDesiredDir(desDir);
			}
		}


		//Update direction:
		void updateDir()
		{
			dir = desiredDir;
		}


		//Update desired direction:
		void updateDesiredDir(int desDir)
		{
			desiredDir = desDir;;
			//Do more?
		}


		void move();
		{
			switch (dir)
			{
				case left: pos[0] -= dt*speed[0];
				break;

				case up: pos[1] += dt*speed[1];
				break;

				case right: pos[0] += dt*speed[0];
				break;

				case down: pos[1] -= dt*speed[1];
				break;

				case still:										//Stays still.
				break;

				default: LOG_DEBUG("Direction out of range.");
				break;
			}

			spriteAnimated.update(pos, dir);					//Call update to run animation.
		}


		//Takes a direction and rotation and returns the next one in the cycle.
		//Either: left->up->right->down-left->up  etc.
		//Or:	  up->left->down->right->up->left etc.
		int cycleDir(int d, int rot)
		{
			if(rot > 0) 										//cycle clockwise.
			{
				return((d%4)+1);
			}
			else												//Cycle counter-clockwise.
			{
				if(d-1 < 1)										//Started at 1/left.
				{
					return down;								//Skip 0/still, skip to down/4.
				}
				else											//Started at up, right or down.
				{
					return (d-1);
				}
			}
		}


		//Checks if player can change direction orthogonal to current direciton(i.e. 90 degree turn):
		bool canTurn()
		{
			//Tile to the relative right or relative left is traversable:
			if(	 level.isTileEmpty(level.findNextTile(tileID, cycleDir(desiredDir,  1))) == true
			  || level.isTileEmpty(level.findNextTile(tileID, cycleDir(desiredDir, -1))) == true)
			{
				return true;
			}
			else												//Cannot make 90 degree turn.
			{
				return false;
			}
		}


		//Each frame, after input possibly changes desiredDir, do:
		void update()
		{
			tPos = level.getTilePos(tileID);					//Updates position of current tile.

			//Can change direction, traversable tile in desired direction:
			if(inTileCenter == true && level.isTileEmpty(level.findNextTile(tileID, desiredDir)) == true)
			{
				//Snaps to tile before changing direction:
				pos = tPos;
				changeDir();
			}

			//Character in center of tile and cannot continue moving in same direction:
			if(inTileCenter == true && level.isTileEmpty(level.findNextTile(tileID, dir)) == false)
			{
				dir = still;									//Sets character to stand still.
			}

			move();												//Change position and update sprite.

			//Character is within the tolerance-value, and is concidered within the center of its current tile:
			if(abs(tPos[0] - pos[0]) < level.retTolerance()[0] && abs(tPos[1] - pos[1]) < level.retTolerance()[1] && inTileCenter == false)
			{
				inTileCenter = true;
																//Pacman enters tile with item to pick up:
				if(type == pacman && level.retTileType(tileID) != empty)
				{
					switch (level.retTileType(tileID))			//Checks for item-type.
					{
						case pellet:							//If pellet.
							gameUI.addScore(SCORE_PELLET);		//Add pellet-score to score total.
						default:
							break;
					}
					level.setTileType(tileID, empty);			//Empty that tile as Pacman has just picked up item.
				}
			}
			else												//Not within tolerance-values.
			{
				inTileCenter = false;
			}
		}

};
