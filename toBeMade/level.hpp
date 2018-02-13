#include <fstream>									//ifstream to load map.
#include <string.h>
#include <string>									//(to_string).
#include "constants.h"

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
		int mapWidth;
		int mapHeight;
		int* tilePtrs;								//Pointer for tile-array.

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
						tilePtrs[i] = new Tile(i, xPos, yPos, tempID);
					}
					else							//Is wall.
					{
						tilePtrs[i] = NULL;			//Set pointer for that tile to NULL.
					}
				}
				reader.close();						//Close ifstream.
			}
			else
			{
				//LOG: "Didn't find the specified level-file.
			}
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


		//Finds adjecant tile, returns -1 if no tile in that direction, -2 if dir is out of range:
		int findNextTile(int ID, int dir)			//‘dir’: 0=left, 1=up, 2=right, 3=down.
		{
			switch(dir)
			{
			case 0: if(ID%mapWidth != 1)			//Not on the left map edge.
					{
						return (ID-1);
					}
					else
					{
						return -1;					//No tile to the left.
					}
			case 1: if(ID/mapWidth != 0)			//Not on the upper map edge.
					{
						return (ID-mapWidth);		//Tile above.
					}
					else
					{
						return -1;					//No tile above.
					}
			case 2: if(ID%mapWidth != 0)			//Not on the rigth map edge.
					{
						return (ID+1);
					}
					else
					{
						return -1;					//No tile to the right.
					}
			case 3: if(ID/mapWidth !=  mapHeight-1)	//Not on the lower map edge.
					{
						return (ID+mapWidth);		//Tile below.
					}
					else
					{
						return -1;					//No tile below.
					}
			default: break;
			}
			return -2;								//‘dir’ neither 0, 1, 2, or 3.
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


		//Returns the type of the tile with the given ID:
		int retTileType(int ID)
		{
			return (tilePtrs[ID]->retType());			//Calls the Tile-objects returnType.
		}
};
