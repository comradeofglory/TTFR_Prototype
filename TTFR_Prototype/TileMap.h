#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class TileMap
{
private:
	int index_search(int index);

public:
	struct tiles
	{
		Vector2i size;
		Vector2i position;
		Vector2i t_position;
		Sprite sprite;
		int collision;
		
		//TODO:
		//animation

		int tile_type;
	};

	struct tile_type {
		int type;
		int collision;
		Texture* texture;
	};

	Vector2i size{0 ,0};
	int tile_type_number = 0;

	tiles* tile = NULL;
	tile_type* type = NULL;

	TileMap();

	void init(std::string LevelFile);

	Vector2f collide(Vector2f char_position, Vector2f char_size, Vector2f char_velocity, short int char_collision);

	Vector2i get_TM_position(Vector2f abs_position);
	int get_tile_collision(Vector2i TM_position);
};
