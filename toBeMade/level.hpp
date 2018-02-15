#include <fstream>									//ifstream to load map.
#include <string.h>
#include <string>									//(to_string).
#include "constants.h"
#include "logger.h"
#include "glm/glm/glm.hpp"
#include "tile.hpp"

// #ifdef _WIN32 // Windows 10 (Visual Studio)
// #define skip
//
// #else  // Linux and Mac OS
//
//
// #endif

//Manages the map:
class Level
{
	private:
		string level;

		//Distance from center which counts as center:
		float cToleranceX;
		float cToleranceY;

		int mapWidth;
		int mapHeight;
		int* tilePtrs;									//Pointer for tile-array.


		//Returns the type of the tile with the given ID:
		int retTileType(int ID)
		{
			return (tilePtrs[ID]->retType());			//Calls the Tile-objects returnType.
		}


		//Finds the furthest open tile in direction ‘dir’, returns ID of that tile or -2 if dir is out of range:
		int findDestination(int ID, int dir)
		{
			if(dir < 0 && dir > 3)					//‘dir’ is out of range.
			{
				return -2;
			}
			else
			{
				bool go = true;
				int tempID = -1;
				int destID = ID;					//ID of the destination-tile, defaults to 'ID'.
				do 									//Keep searching neighbour until neibour is not empty:
				{
					tempID = findNextTile(ID, dir);	//Sets 'destID' to next neighbour.
					if(isTileEmpty(tempID))			//The tile with ID 'tempID' is empty, it's not NULL.
					{
						destID = tempID;			//neighbour is a tile, save as destination.
					}
					else							//We hit a wall in our search.
					{
						go = false;					//Stop checking neighbour.
					}
				} while(go);

				return destID;						//Returns the ID of open tile furthest in direction 'dir'.
			}
		}


	public:
		//Constructor:
		//Sets its variables and reads level-file to create tiles for tile-pointer array:
		Level(int lvl)
		{
			level = "level" + to_string(lvl);		//Dynamic string to load levels dynamically.

			ifstream reader("../levels/" + level);	//Creates ifstream to read level-file.

			if(reader)								//Found the file.
			{
				reader >> mapWidth;
				reader >> mapHeight;
				reader.ignore();					//Ignore newline.

				tilePtrs = new int[mapWidth*mapHeight];

				int k = mapWidth*mapHeight;
				int tempID;
				int horizIncrement = HORIZONTAL_GAMESPACE/mapWidth;
				int vertiIncrement = VERTICAL_GAMESPACE/mapHeight;
				int tSizeX = (2*HORIZONTAL_GAMESPACE)/mapWidth;
				int tSizeY = (2*VERTICAL_GAMESPACE)/mapHeight;
				int xPos, yPos;

				for (int i = 0; i < k; i++) 		//Reads level-file and creates tiles.
				{
					reader >> tempID;
					if(tempID != 1)					//Not wall.
					{
													//'-1.0f' is left border, then add padding.
													//'HORIZONTAL_GAMESPACE' determines padding,
													//add 'horizIncrement' per previous element in row.
													//'i%mapWidth' gives number for that row.
													//Formula: Borderpos + padding + increment.
						xPos = (-1+(2-HORIZONTAL_GAMESPACE*2))+((i%mapWidth)*horizIncrement);
													//'1.0f' is upper border, then add padding.
													//'VERTICAL_GAMESPACE' determines padding.
													//add 'vertiIncrement' per previous element in column.
													//'i/mapHeight' gives number for that column.
													//Formula: Borderpos - padding - increment.
						yPos = (1-(2-VERTICAL_GAMESPACE*2))-((i/mapHeight)*vertiIncrement);

													//Add new tile and make index 'i' in array point to it.
						tilePtrs[i] = new Tile(i, glm::vec2(xPos, yPos), glm::vec2(tSizeX, tSizeY), tempID);
					}
					else							//Is wall.
					{
						tilePtrs[i] = NULL;			//Set pointer for wall to NULL.
					}
				}
				reader.close();						//Close ifstream.
			}
			else
			{
				LOG_DEBUG("Didn't find the specified level-file.");
			}

			//Finished loading variables from file, set tolerance-variables.

			//The tolerance scales with the Gamespace-factor and the amount of tiles in each dimention.
			//2*HORIZONTAL_GAMESPACE = width of map in world space coordinates.
			//(1/mapWidth) = Fraction of gamespace occupied by a single tile.
			//2*HORIZONTAL_GAMESPACE*(1/mapWidth) = (width of gamespace) / (number of tiles in a row).
			//2*HORIZONTAL_GAMESPACE*(1/mapWidth) = size of a single tile.
			//Translated: CENTER_TOLERANCE * (Size of tile).
			//E.G. Given CENTER_TOLERANCE of 0.5f, cToleranceX will be 50% of a single tile's x-dimention.
			cToleranceX = CENTER_TOLERANCE*2*HORIZONTAL_GAMESPACE*(1/mapWidth);	//Fraction of tile-size.
			cToleranceY = CENTER_TOLERANCE*2*VERTICAL_GAMESPACE*(1/mapHeight);	//Fraction of tile-size.

		}


		//Deconstructor:
		~Level()
		{
			delete tilePtrs;
		}

		//Return Width:
		int retW()
		{
			return mapWidth;
		}


		//Return Height:
		int retH()
		{
			return mapHeigth;
		}


		//Returns a pointer to array with subcoordinates of tile with given ID:
		glm::vec2 getTilePos(int ID)
		{
			if(ID < 0 || ID > (mapWidth*mapHeight)-1)//ID is not in range.
			{
				LOG_DEBUG("Did not fetch position of tile since ID is out of range.");
				return glm::vec2(-2, -2);
			}
			else									//ID is in range.
			{
				return (tilePtrs[ID]->retPos());	//Fetch position from wanted tile.
			}
		}


		//Takes ID of current position's tile-ID, and direction dir,
		//returns pointer to array with x and y position of tile farthest
		//in the given direction:
		glm::vec2 getDestinationPos(int ID, int dir)		//‘dir’: 0=left, 1=up, 2=right, 3=down.
		{
			return(getTilePos(findDestination(ID, dir)));		//Finds dest + fetch pos.
		}


		//Finds adjecant tile, returns -1 if no tile in that direction, -2 if dir is out of range:
		int findNextTile(int ID, int dir)			//‘dir’: 0=left, 1=up, 2=right, 3=down.
		{
			switch(dir)
			{
			case left: if(ID%mapWidth != 1)			//Not on the left map edge.
					{
						return (ID-1);
					}
					else
					{
						return -1;					//No tile to the left.
					}
			case up: if(ID/mapWidth != 0)			//Not on the upper map edge.
					{
						return (ID-mapWidth);		//Tile above.
					}
					else
					{
						return -1;					//No tile above.
					}
			case right: if(ID%mapWidth != 0)		//Not on the rigth map edge.
					{
						return (ID+1);
					}
					else
					{
						return -1;					//No tile to the right.
					}
													//Not on the lower map edge.
			case down: if(ID/mapWidth !=  mapHeight-1)
					{
						return (ID+mapWidth);		//Tile below.
					}
					else
					{
						return -1;					//No tile below.
					}
			default: break;
			}
			return -2;								//‘dir’ neither left, up, right or down.
		}


		//Gets type from a tile in array and returns it:
		bool isTileEmpty(int ID)
		{
			if(ID < 0 || ID > (mapWidth*mapHeight)-1)	//ID is not within range.
			{
				return 0;
			}
			else										//ID is within range.
			{
				if(tiles[ID] != NULL)					//Tile with that ID exists.
				{
					return 1;
				}
				else									//Tile does not exist(wall).
				{
					return 0;
				}
			}
		}


		float* retTolerance()
		{
			float* floatPtr = new float[cToleranceX, cToleranceY];
			return floatPtr;
		}

};
