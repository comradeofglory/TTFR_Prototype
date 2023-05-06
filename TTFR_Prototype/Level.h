#pragma once
#include "TileMap.h"
#include "Barrier.h"
#include "Character.h"

class Level
{
private:

public:
	TileMap tile_map;
	Character player;
	std::vector<Character> enemies;
	Barrier b;

	void init(std::string tile_map_file);

	void input(Vector2f direction) {
		player.body.set_acceleration(direction);
	}

	void logic();

	
};
