#pragma once
#include <SFML/Graphics.hpp>
#include "TileMap.h"
using namespace sf;

class KinematicBody
{
private:
	Vector2f size, position, velocity;
	int collision;
public:
	void init(Vector2f _size, Vector2f _position, int _collision);
	void set_velocity(Vector2f _veclocity);
	void move(TileMap* TM /*Bodies*/);
	Vector2f collide(Vector2f obj_size, Vector2f obj_position, Vector2f obj_speed, int obj_collision);
};

