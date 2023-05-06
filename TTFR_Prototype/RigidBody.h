#pragma once
#include <SFML/Graphics.hpp>
#include "TileMap.h"
#include "GMath.h"

using namespace sf;

class RigidBody
{
private:
	float mass, friction;
	int collision;
public:
	Vector2f position, size, velocity, acceleration;
	void init(Vector2f _position, Vector2f _size, float _mass, float _friction, int _collision);
	void set_velocity(Vector2f _velocity);
	void set_acceleration(Vector2f _acceleration);

	bool collide(RigidBody* other_rb);
	void move(TileMap* TM, std::vector<RigidBody*> chars_params);
};