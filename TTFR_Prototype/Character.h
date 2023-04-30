#pragma once
#include <SFML/Graphics.hpp>
#include "RigidBody.h"
using namespace sf;

class Level;

class Character
{
public:
	RigidBody body;
	RectangleShape shape;

	Character() {};
	~Character() {};

	void init(Vector2f position, Vector2f size);
	void move(TileMap* tile_map, Level *level/*, std::vector<Character> *entities*/);
};
