#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class StaticBody
{
private:
	Vector2f size, position;
	int collision;
public:
	void init(Vector2f _size, Vector2f _position, int _collision);
	Vector2f collide(Vector2f obj_size, Vector2f obj_position, Vector2f obj_speed, int obj_collision);
};

