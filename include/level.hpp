#pragma once

#include <fstream>												//ifstream to load map.
#include <string.h>
#include <string>												//(to_string).
#include "constants.h"
#include "logger.h"
#include "glm/glm/glm.hpp"
#include "tile.hpp"
#include <vector>
// #include "gameloop.hpp"	Circle include


// extern GameLoop gameLoop;


//Manages the map:
class Level
{
	private:
		std::string level;

		//Distance from center which counts as center:
		float cToleranceX;
		float cToleranceY;

		glm::vec2 tSize;

		int mapWidth;
		int mapHeight;
		int numberOfTiles;
		int itemsRemaining;										//When it reaches zero, the player wins.
 		std::vector<Tile> tiles;								//Pointer for tile-array.
		std::vector<int> warps;
		std::vector<int> ghosts;
		int pacmanSpawnTileID;


	public:

		Level() = default;

		Level& operator=(const Level& other) = default;
		//Constructor:
		//Sets its variables and reads level-file to create tiles for tile-pointer array:
		Level(int lvl)
		{
			level = "./levels/level" + std::to_string(lvl);		//Dynamic string to load levels dynamically.

			std::ifstream reader(level);						//Creates ifstream to read level-file.

			itemsRemaining = 0;

			if(reader)											//Found the file.
			{
				reader >> mapWidth;
				reader >> mapHeight;
				reader.ignore();								//Ignore newline.

				numberOfTiles = mapWidth*mapHeight;

				LOG_DEBUG("k: %d'", numberOfTiles);


				char tempID;
				tSize = glm::vec2((2*HORIZONTAL_GAMESPACE)/float(mapWidth), (2*VERTICAL_GAMESPACE)/float(mapHeight));
				LOG_DEBUG("tSize calculated: %f, %f", tSize.x, tSize.y);
				float xPos, yPos;

				for (int i = 0; i < numberOfTiles; i++) 		//Reads level-file and creates tiles.
				{
					reader >> tempID;							//Reads character from level-file.

																//'1-HORIZONTAL_GAMESPACE = Padding.
																//'i%mapWidth' gives number for that row.
																//Formula: Borderpos + padding + increment.
																// -1 + ( /2)
					xPos = (-1.0f+(1-HORIZONTAL_GAMESPACE)+((i%mapWidth)*tSize.x));
					yPos = ((1.0f-(1-VERTICAL_GAMESPACE))-((i/mapWidth)*tSize.y));

					//Compares char from level-file to const-values set in 'constants.h'.
					switch (tempID)
					{
						case LEVEL_WALL:
							//Add new tile to index 'i' in tiles-vector.
							tiles.push_back(Tile(i, glm::vec2(xPos, yPos), tSize, wall));
							break;

						case LEVEL_EMPTY:
							//Add new tile to index 'i' in tiles-vector.
							tiles.push_back(Tile(i, glm::vec2(xPos, yPos), tSize, empty));
							break;

						case LEVEL_PELLET:
							//Add new tile to index 'i' in tiles-vector.
							tiles.push_back(Tile(i, glm::vec2(xPos, yPos), tSize, pellet));
							itemsRemaining ++;					//Counts score you need to win.
							break;

						case LEVEL_PACMAN:
							//Add new tile to index 'i' in tiles-vector.
							tiles.push_back(Tile(i, glm::vec2(xPos, yPos), tSize, empty));
							pacmanSpawnTileID = i;				//Saving index of tile to variable.
							break;

						case LEVEL_GHOST:
							//Add new tile to index 'i' in tiles-vector.
							tiles.push_back(Tile(i, glm::vec2(xPos, yPos), tSize, pellet));
							ghosts.push_back(i);				//Save the tile-ID in ghosts-vector.
							break;

						case LEVEL_WARP:
							//Add new tile to index 'i' in tiles-vector.
							tiles.push_back(Tile(i, glm::vec2(xPos, yPos), tSize, empty));
							warps.push_back(i);						//Save the tile-ID in warps-vector.
							break;

						default:
							tiles.push_back(Tile(i, glm::vec2(xPos, yPos), tSize, empty));
							LOG_DEBUG("Unknown character in file!");
							break;
					}

				}
				LOG_DEBUG("Loop has ended");
				reader.close();						//Close ifstream.
			}
			else
			{
				LOG_ERROR("Didn't find the specified level-file.");
			}

			//Finished loading variables from file, set tolerance-variables.

			//The tolerance scales with the Gamespace-factor and the amount of tiles in each dimention.
			//2*HORIZONTAL_GAMESPACE = width of map in world space coordinates.
			//(1/mapWidth) = Fraction of gamespace occupied by a single tile.
			//2*HORIZONTAL_GAMESPACE*(1/mapWidth) = (width of gamespace) / (number of tiles in a row).
			//2*HORIZONTAL_GAMESPACE*(1/mapWidth) = size of a single tile.
			//Translated: CENTER_TOLERANCE * (Size of tile).
			//E.G. Given CENTER_TOLERANCE of 0.5f, cToleranceX will be 50% of a single tile's x-dimention.
			cToleranceX = CENTER_TOLERANCE*2*HORIZONTAL_GAMESPACE*(1/float(mapWidth));	//Fraction of tile-size.
			cToleranceY = CENTER_TOLERANCE*2*VERTICAL_GAMESPACE*(1/float(mapHeight));	//Fraction of tile-size.

		}


		int retStartTileID()
		{
			return pacmanSpawnTileID;
		}


		std::vector<int> retWarpVector()
		{
			return warps;
		}


		std::vector<int> retGhostVector()
		{
			return ghosts;
		}


		//Returns the type of the tile with the given ID:
		Texture retTileType(int ID)
		{
			return  tiles[ID].retType();						//Calls the Tile-objects returnType.
		}


		//Return Width:
		int retW()
		{
			return mapWidth;
		}


		//Return Height:
		int retH()
		{
			return mapHeight;
		}


		glm::vec2 retTSize()
		{
			return tSize;
		}


		//Returns a pointer to array with subcoordinates of tile with given ID:
		glm::vec2 getTilePos(int ID)
		{
			if(ID < 0 || ID > (mapWidth*mapHeight)-1)//ID is not in range.
			{
				LOG_DEBUG("Did not fetch position of tile since ID is out of range.");
				return glm::vec2(-2, -2);
			}
			else												//ID is in range.
			{
				return  tiles[ID].retPos();						//Fetch position from wanted tile.
			}
		}


//Entered spawn-tile, ID: 477. Direction: left, next tileID: -1

		//Finds adjecant tile, returns -1 if no tile in that direction, -2 if dir is out of range:
		int findNextTile(int ID, int dir)						//???dir???: 1=left, 2=up, 3=right, 4=down.
		{
			switch(dir)
			{
			case left: if(ID%mapWidth != 0)						//Not on the left map edge.
					{
						return (ID-1);
					}
					else
					{
						return -1;								//No tile to the left.
					}
			case up: if(ID/mapWidth != 0)						//Not on the upper map edge.
					{
						return (ID-mapWidth);					//Tile above.
					}
					else
					{
						return -1;								//No tile above.
					}
			case right: if(ID%mapWidth != mapWidth-1)			//Not on the rigth map edge.
					{
						return (ID+1);
					}
					else
					{
						return -1;								//No tile to the right.
					}
																//Not on the lower map edge.
			case down: if(ID/mapWidth !=  mapHeight-1)
					{
						return (ID+mapWidth);					//Tile below.
					}
					else
					{
						return -1;								//No tile below.
					}
			default: break;
			}
			return -2;											//???dir??? neither left, up, right or down.
		}


		//Gets type from a tile in array and returns it:
		bool isTileEmpty(int ID)
		{
			if(ID < 0 || ID > (mapWidth*mapHeight)-1)			//ID is not within range.
			{
				return 0;
			}
			else												//ID is within range.
			{
				if(tiles[ID].retTexture() != wall)				//Tile with that ID exists.
				{
					return 1;
				}
				else											//Tile does not exist(wall).
				{
					return 0;
				}
			}
		}


		//Returns tolereanc-value of center.
		glm::vec2 retTolerance()
		{
			return glm::vec2(cToleranceX, cToleranceY);
		}


		int retItemsRemaining()
		{
			return itemsRemaining;
		}


		//Changes a tiles type.
		void setTileType(int Id, Texture t)
		{
			tiles[Id].setType(t);
		}


		void draw()
		{
			//gameLoop.endLoop(); 	//testing circle include probelm
			for (int i = 0; i < numberOfTiles; i++)
			{
				tiles[i].draw();
			}
		}
};
