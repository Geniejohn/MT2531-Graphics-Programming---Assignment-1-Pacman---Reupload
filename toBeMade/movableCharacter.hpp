#include "sprite.hpp"
#include "logger.h"

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
		Sprite sprite;

	public:
		//Constructor:
		MovableCharacter(int Id, int x, int y, int typ)
		{
			xPos = x;
			yPos = y;
			type = typ;
			dir = 2;											//Right.
			desiredDir = 2;										//Right.
			sprite = new AnimatedSprite(typ);					//Creates new sprite of wanted type.
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
		void changeDir(int d)
		{
			if(d < 0 || d > 3)									//'d' out of range.
			{
				LOG_DEBUG("Direction-argument is out of range(0-3).");
			}
			else												//'d' in range.
			{
				updateDir(d);
			}
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
		void updateDir(int d)
		{
			dir = d;
			//Update sprites etc.
		}


		//Update desired direction:
		void updateDesiredDir(int d)
		{
			defesiredDir = desDir;;
			//Do more?
		}


};
