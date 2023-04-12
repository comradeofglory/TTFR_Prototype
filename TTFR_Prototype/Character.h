#pragma once
#include <SFML/Graphics.hpp>
#include "TileMap.h"
using namespace sf;

class Character
{
private:
	//short int HP;
public:
	Vector2f position, size, center;
	Vector2f velocity, control_velocity;
	RectangleShape sprite;
	Texture texture;
	short int collision;  

	//debug
	Font font;
	Text text;
	String debug;
	//

	void init(Vector2f _position, Vector2f _size, Texture _texture, short int _collision);
	void set_velocity(Vector2f _velocity);
	void move(TileMap tile_map);
};
