#pragma once
#include <SFML/Graphics.hpp>
#include "StaticBody.h"

class Barrier
{
public:
	StaticBody body;
	RectangleShape shape;
	void init(Vector2f position, Vector2f size, int collision);
};

