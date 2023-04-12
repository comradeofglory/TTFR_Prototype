#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class GameMath
{
public:
	Vector2f Normalised(Vector2f vector);
	float Length(Vector2f vector);
};

