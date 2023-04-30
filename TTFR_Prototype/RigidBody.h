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
	Vector2f collide(Vector2f obj_size, Vector2f obj_position, Vector2f obj_speed, int obj_collision);
	void move(TileMap* TM, Level *level/*, std::vector<Character> *entities*/ /*barriers, objects*/);
};

