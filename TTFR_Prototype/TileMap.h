#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"

using namespace sf;

class TileMap
{
private:
public:
	Vector2i size;
	Tile* tile = new Tile[size.x*size.y];

	void init(); 
};

