#include "sprite.hpp"
#include "logger.h"
#include "level.hpp"
#include "glm/glm/glm.hpp"
#include "spriteAnimated.hpp"
#include "cmath"												// abs()

//extern level;

//Base-class for all movable characters:
class MovableCharacter
{
	private:
		int xPos;												//X coordinate.
		int yPos;												//Y coordinate.
		int type;												//Enum for character-type.
		SpriteAnimated spriteAnimated;
		bool inTileCenter;

	protected:
		int dir;												//Current movement-direction.
		int desiredDir;											//Desired movement-direction.
		int tileID;												//ID the tile occupied by character.
		glm::vec2 tPos;

	public:
		//Constructor:
		MovableCharacter(int Id, int typ)
		{
			spriteAnimated = new SpriteAnimated(typ);			//Creates new sprite of wanted type.
			inTileCenter = true;								//Starts in center of tile.
			tileID = Id;
			xPos = level.getTilePos()[0];
			yPos = level.getTilePos()[1];
			type = typ;
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
			return glm::vec2(xPos, yPos);
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
				//case left: xPos -= deltaTime*speed;
				//break;

				//case up: yPos += deltaTime*speed;
				//break;

				//case right: xPos += deltaTime*speed;
				//break;

				//case down: xPos -= deltaTime*speed;
				//break;

				//case still:										//Stays still.
				//break;

				default: LOG_DEBUG("Direction out of range.");
				break;
			}

			spriteAnimated.update(glm::vec2(xPos, yPos), dir);	//Call update to run animation.
		}


		//Each frame, after input possibly changes desiredDir, do:
		void update()
		{
			tPos = level.getTilePos(tileID);					//Updates position of current tile.

			//Can change direction, traversable tile in desired direction:
			if(inTileCenter == true && level.isTileEmpty(level.findNextTile(tileID, desiredDir)) == true)
			{
				//Snaps to tile before changing direction:
				xPos = tPos[0];
				yPos = tPos[1];

				changeDir();
			}

			//Character in center of tile and cannot continue moving in same direction:
			if(inTileCenter == true && level.isTileEmpty(level.findNextTile(tileID, dir)) == false)
			{
				dir = still;									//Sets character to stand still.
			}

			move();												//Change position and update sprite.

			//Character is within the tolerance-value, and is concidered within the center of its current tile:
			if(abs(tPos[0] - xPos) < level.retTolerance()[0] && abs(tPos[1] - yPos) < level.retTolerance()[1])
			{
				inTileCenter = true;
			}
			else												//Not within tolerance-values.
			{
				inTileCenter = false;
			}
		}

};
