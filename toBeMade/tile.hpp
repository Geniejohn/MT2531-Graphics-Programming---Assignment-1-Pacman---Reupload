#include "sprite.hpp"
#include "constants.h"

//Each space in the map except for the walls are tiles:
class Tile
{
	private:
		int ID;
		int x;										//X coordinate.
		int y;										//Y coordinate.
		int type;
		Sprite* sprite;

	public:
		//Constructor:
		Tile(int Id, int xPos, int yPos, int typ)
		{
			x = xPos;
			y = yPos;
			type = typ;
			sprite = new Sprite(typ);				//Creates new sprite of the wanted type.
		}


		//Deconstructor:
		~Tile()
		{
			delete sprite;
		}


		int retType()
		{
			return type;
		}

		int retX()
		{
			return x;
		}


		int retY()
		{
			return y;
		}
};
