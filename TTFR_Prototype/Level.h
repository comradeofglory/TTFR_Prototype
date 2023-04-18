#pragma once
#include "TileMap.h"
#include "CharacterMaster.h"
#include "Barrier.h"
#include "GameMath.h"

class Level
{
private:
public:
	TileMap tile_map;
	//CharacterMaster character_master;
	Character player;
	GameMath math;
	Barrier b;


	void input(Vector2f direction) {
		player.body.set_acceleration(direction);
	}
	void logic() {
		player.body.move(&tile_map);
		player.shape.setPosition(player.body.position);
	}
	void init(std::string tile_map_file);
};
