#pragma once
#include <SFML/Graphics.hpp>
#include "RigidBody.h"
using namespace sf;

class Character
{
public:
	RigidBody body;
	RectangleShape shape;

	void init(Vector2f position, Vector2f size);

};
