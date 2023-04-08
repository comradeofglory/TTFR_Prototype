#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class TileMap
{
private:
	struct tiles
	{
		Vector2i size;
		Vector2i position;
		Vector2i t_position;
		
		int collision;
		//TODO:
		//animation
		
		int tile_type;
	};

	struct tile_type {
		int type;
		Sprite sprite;
		Texture texture;
	};
public:
	Vector2i size;
	int tile_type_number;

	tiles* tile = new tiles[size.x*size.y];
	tile_type* type = new tile_type[tile_type_number];




	void init(); 
	Vector2i collide(Vector2i ch_position, Vector2i ch_size, Vector2i ch_velocity, short int ch_collision); //Принимает позицию и скорость юнита, возвращает скорость юнита с учетом коллизии
};

