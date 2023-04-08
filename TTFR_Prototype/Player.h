#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;


class Player
{
public:
	Vector2f position, velocity, size;
	Sprite sprite;
	int collider = 1;
};