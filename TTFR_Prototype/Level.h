#pragma once
#include "TileMap.h"
#include "CharacterMaster.h"

class Level
{
private:
public:
	TileMap tile_map;
	//CharacterMaster character_master;
	Character player;


	void input(Vector2f direction) {
		player.set_velocity(direction * (float)4);
	}
	void logic() {
		player.move(tile_map);
	}
	void init(std::string tile_map_file);
};
