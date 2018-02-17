#pragma once
#include <cmath>												// abs()
#include "glm/glm/glm.hpp"
#include "logger.h"
#include "spriteAnimated.hpp"
#include "level.hpp"
#include "pacman.hpp"
#include <vector>

extern Level level;
extern float dt;												//DeltaTime.
// extern GameUI gameUI;

//Base-class for all movable characters:
class MovableCharacter
{
	private:
		Animation type;											//Enum for character-type.
		glm::vec2 speed;
		SpriteAnimated spriteAnimated;
		bool inTileCenter;
		bool firstChoice;

	protected:
		glm::vec2 pos;
		int dir;												//Current movement-direction.
		int desiredDir;											//Desired movement-direction.
		int tileID;												//ID the tile occupied by character.
		glm::vec2 tPos;											//Positioin of tile we are in.
		glm::vec2 desTPos;										//Position of tile we are movinw towards.

	public:
		//Constructor:

		MovableCharacter() = default;


		MovableCharacter& operator =(const MovableCharacter& other) = default;


		MovableCharacter(int Id, Animation typ, glm::vec2 s)
		{
			inTileCenter = true;								//Starts in center of tile.
			tileID = Id;
			type = typ;
			speed = s;
			pos = level.getTilePos(tileID);
																//Creates new sprite of wanted type:
			spriteAnimated = SpriteAnimated(pos, level.retTSize(), type);
			dir = STARTING_DIRECTION;
			desiredDir = STARTING_DIRECTION;
			tPos = level.getTilePos(tileID);					//Sets pos of current tile.
			desTPos = level.getTilePos(level.findNextTile(tileID, desiredDir));
			//LOG_DEBUG("tPos: %f, %f (Position where the entity spawns)", tPos.x, tPos.y);
		}


		//Deconstructor:
		~MovableCharacter()
		{

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
				LOG_DEBUG("Desired direction-argument is out of range(0-4).");
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
			desiredDir = desDir;
			LOG_DEBUG("Desired direction: %d", desiredDir);
			LOG_DEBUG("Current direction: %d", dir);
		}


		void move()
		{
			//LOG_DEBUG("move(): dir: %d", dir);
			switch (dir)
			{
				case still:										//Stays still.
				break;

				case left: 	pos.x -= dt*speed.x;
				break;

				case up: 	pos.y += dt*speed.y;
				break;

				case right: pos.x += dt*speed.x;
				break;

				case down: 	pos.y -= dt*speed.y;
				break;

				default: LOG_DEBUG("Direction out of range: %d", dir);
				break;
			}

			spriteAnimated.update(pos, Direction(dir));					//Call update to run animation.
			// LOG_DEBUG("Speed: %f, %f", speed.x, speed.y);
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
			if(	(level.isTileEmpty(level.findNextTile(tileID, cycleDir(desiredDir, 1))) == true
			  || level.isTileEmpty(level.findNextTile(tileID, cycleDir(desiredDir, 0))) == true)
		  	  && firstChoice == true)
			{
				return true;
			}
			else												//Cannot make 90 degree turn.
			{
				return false;
			}
		}


		//Returns true if desiredDir is opposite of dir:
		bool isUTurn()
		{
			//Left:1, Up:2, Right:3, Down:4:
			if(abs(desiredDir - dir) == 2)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}

		//Each frame, after input possibly changes desiredDir, do:
		void update()
		{
			tPos = level.getTilePos(tileID);					//Updates position of current tile.

			if(desiredDir != dir)
			{
				//Can change direction, traversable tile in desired direction:
				if((inTileCenter == true || isUTurn() == true) && level.isTileEmpty(level.findNextTile(tileID, desiredDir)) == true)
				{
					//Snaps to tile before changing direction:
					if(isUTurn() == false)
					{
						pos = tPos;
					}
					changeDir();
					desTPos = level.getTilePos(level.findNextTile(tileID, dir));
				}
			}

			//Character in center of tile and cannot continue moving in same direction:
			if(inTileCenter == true && level.isTileEmpty(level.findNextTile(tileID, dir)) == false)
			{
				dir = still;									//Sets character to stand still.
			}

			move();												//Change position and update sprite.

			//Checks if character has entered a new tile:
			if(abs(desTPos.x - pos.x) < level.retTSize().x/2.0f && abs(desTPos.y - pos.y) < level.retTSize().y/2.0f)
			{
				tileID = level.findNextTile(tileID, dir);		//Sets new current-tile.
																//Updates position of destination-tile:
				desTPos = level.getTilePos(level.findNextTile(tileID, dir));
			}

			//Character is within the tolerance-value, and is concidered within the center of its current tile:
			if(abs(tPos.x - pos.x) < level.retTolerance().x && abs(tPos.y - pos.y) < level.retTolerance().y && inTileCenter == false)
			{
				firstChoice = true;
				inTileCenter = true;
				if(type == pacman)								//Is Pacman.
				{
					if(level.retTileType(tileID) != empty)		//Tile entered is empty.
					{
						switch (level.retTileType(tileID))		//Checks for item-type.
						{
							case pellet:						//If pellet.
							//gameUI.addScore(SCORE_PELLET);	//Add pellet-score to score total.
							default:
							break;
						}
						level.setTileType(tileID, empty);		//Empty that tile as Pacman has just picked up item.
						// LOG_DEBUG("Entered center of non-empty tile.");
					}

																//Gets vector with warp-ID's.
					std::vector<int> warps = level.retWarpVector();
					for (int i = 0; i < warps.size(); i++)
					{
						if(tileID == warps[i])					//We entered a warp-tile.
						{
							tileID = warps[(i+1)%(warps.size())];
							pos = level.getTilePos(tileID);		//Sets position to next warp in cycle.

																//Updates position of destination-tile:

																//Next tile afte warp is not traversable.
							if(level.isTileEmpty(level.findNextTile(tileID, dir)) == false)
							{
								//While our direction leads to a wall:
								while(level.isTileEmpty(level.findNextTile(tileID, dir)) == false)
								{
									dir = cycleDir(dir, 1);		//Change direction.
								}
								//Now dir leads to a traversable tile,
								//set destination position to that one:
								desTPos = level.getTilePos(level.findNextTile(tileID, dir));

								//Sets to still as to not confuse player.
								desiredDir = still;
								dir = still;
							}
							desTPos = level.getTilePos(level.findNextTile(tileID, dir));
						}
					}
				}
																//Pacman enters tile with item to pick up:
				// LOG_DEBUG("Entered center of new tile.");
			}

			//If character is not within the tolerance value if its current-tile, set bool inTileCenter to false:
			if(abs(tPos.x - pos.x) > level.retTolerance().x || abs(tPos.y - pos.y) > level.retTolerance().y)											//Not within tolerance-values.
			{
				inTileCenter = false;
				firstChoice = false;
			}
		}

		void draw()
		{
			spriteAnimated.draw();
		}

};
