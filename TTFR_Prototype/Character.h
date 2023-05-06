#pragma once
#include <SFML/Graphics.hpp>
#include "RigidBody.h"

using namespace sf;

class Character
{
public:
	RigidBody body;
	RectangleShape shape;

	Character() {};
	~Character() {};

	void init(Vector2f position, Vector2f size, int coll);
	void move(TileMap* tile_map, std::vector<RigidBody*> chars_rbodies);
};
