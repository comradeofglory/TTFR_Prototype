#pragma once
#include "TileMap.h"
#include "CharacterMaster.h"

class Level
{
private:
public:
	TileMap tile_map;
	//CharacterMaster character_master;

	void init(std::string tile_map_file);
};
