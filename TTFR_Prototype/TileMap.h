#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class TileMap
{
private:
	

public:
	struct tiles
	{
		Vector2i size;
		Vector2i position;
		Vector2i t_position;
		Sprite sprite;
		
		//TODO:
		//animation

		int tile_type;
	};

	struct tile_type {
		int collision;
		Texture* texture;
	};

	Vector2i size{0 ,0};
	int tile_type_number = 0;

	tiles* tile = NULL;
	tile_type* type = NULL;



	TileMap();

	void init(std::string LevelFile);
	Vector2i collide(Vector2i ch_position, Vector2i ch_size, Vector2i ch_velocity, short int ch_collision);
};
