#pragma once

#include "sprite.hpp"
#include "constants.h"
#include "glm/glm/glm.hpp"
#include "logger.h"
#include <string>

//Each space in the map except for the walls are tiles:
class Tile
{
	private:
		int ID;
		glm::vec2 pos;
		glm::vec2 size;
		Texture type;									//Texture Enum.
		Sprite sprite;

	public:
		//Constructor:
		Tile(int Id, glm::vec2 p, glm::vec2 s, Texture typ)
		{
			ID = Id;
			pos = p;
			size = s;
			type = typ;
			//LOG_DEBUG("posX: %f, posY: %f, sizeX: %f, sizeY: %f, Texture: %d", pos.x, pos.y, size.x, size.y, typ);

			sprite = Sprite(pos, size, type);				//Creates new sprite of the wanted type.

		}


		//Deconstructor:
		~Tile()
		{

		}


		Texture retType()
		{
			return type;
		}


		glm::vec2 retPos()
		{
			return pos;
		}


		//Called by level when pacman eats a pellet for example:
		void setType(Texture t)
		{
			type = t;
			sprite.setTexture(type);
		}


		Texture retTexture()
		{
			return type;
		}


		void draw()
		{
			sprite.draw();
		}

};
