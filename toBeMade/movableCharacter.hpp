#include "sprite.hpp"
#include "logger.h"
#include "level.hpp"
#include "glm/glm/glm.hpp"
#include "spriteAnimated.hpp"


//Each space in the map except for the walls are tiles:
class MovableCharacter
{
	private:
		int tileID;												//ID the tile occupied by character.
		int xPos;												//X coordinate.
		int yPos;												//Y coordinate.
		int type;												//Enum for character-type.
		int dir;												//Current movement-direction.
		int desiredDir;											//Desired movement-direction.
		SpriteAnimated spriteAnimated;
		bool inTileCenter;
		Level level;

	public:
		//Constructor:
		MovableCharacter(int Id, int x, int y, int typ)
		{
			inTileCenter = true;								//Starts in center of tile.
			tileID = Id;
			xPos = x;
			yPos = y;
			type = typ;
			dir = 2;											//Right.
			desiredDir = 2;										//Right.
			spriteAnimated = new SpriteAnimated(typ);			//Creates new sprite of wanted type.
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


		int* retPos()
		{
		 	int* pos = new int[2];
			pos = {xPos, yPos};
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
			if(d < 0 || d > 3)									//'d' out of range.
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
		void updateDesiredDir(int d)
		{
			defesiredDir = desDir;;
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
			//Can change direction, traversable tile in desired direction:
			if(inTileCenter == true && level.findNextTile(tileID, desiredDir))
			{
				int* tPos = level.getTilePos(tileID);			//Finds position of current tile.

				//Snaps to tile before changing direction:
				xPos = tPos[0];
				yPos = tPos[1];

				changeDir();
			}

			move();												//Change position and update sprite.
		}

};
