#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Area
{
private:
	Vector2f size, position;
public:
	bool collide(Vector2f obj_position, Vector2f obj_size);
};

