#include "sprite.hpp"
#include "constants.h"
#include "glm/glm/glm.hpp"

//Each space in the map except for the walls are tiles:
class Tile
{
	private:
		int ID;
		glm::vec2 pos;
		glm::vec2 size;
		int type;									//Texture Enum.
		Sprite* sprite;

	public:
		//Constructor:
		Tile(int Id, glm::vec2 p, glm::vec2 s, int typ)
		{
			ID = Id;
			pos = p;
			size = s;
			type = typ;
			sprite = new Sprite(pos, size, typ);				//Creates new sprite of the wanted type.
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


		glm::vec2 retPos()
		{
			return pos;
		}


		//Called by level when pacman eats a pellet for example:
		void setType(int t)
		{
			type = t;
			sprite.setTexture(type);
		}

};
