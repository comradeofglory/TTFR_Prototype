#include "RigidBody.h"


void RigidBody::init(Vector2f _position, Vector2f _size, float _mass, float _friction, int _collision) {
	position = _position;
	size = _size;
	mass = _mass;
	friction = _friction;
	collision = _collision;
}

void RigidBody::set_velocity(Vector2f _velocity) {
	velocity = _velocity;
}

void RigidBody::set_acceleration(Vector2f _acceleration) {
	acceleration = _acceleration;
}

Vector2f RigidBody::collide(Vector2f obj_size, Vector2f obj_position, Vector2f obj_speed, int obj_collision) {
	Vector2f res_velocity = obj_speed;

	if (obj_collision > collision) {
		return obj_speed;
	}

	if (obj_position.x + obj_speed.x < position.x + size.x &&
		obj_position.x + obj_speed.x + obj_size.x > position.x &&
		obj_position.y < position.y + size.y &&
		obj_position.y + obj_size.y > position.y)
	{
		res_velocity.x = 0;
		//TODO: interpolation
		if (obj_position.x > position.x + size.x) {
			res_velocity.x = obj_position.x - position.x + size.x + 0.1;
		}
		if (obj_position.x + obj_position.x < position.x) {
			res_velocity.x = position.x - obj_position.x - obj_size.x - 0.1;
		}
	}
	if (obj_position.x < position.x + size.x &&
		obj_position.x + obj_size.x > position.x &&
		obj_position.y + obj_speed.y < position.y + size.y &&
		obj_position.y + obj_speed.y + obj_size.y > position.y)
	{
		res_velocity.y = 0;
		//TODO: interpolation
		if (obj_position.y > position.y + size.y) {
			res_velocity.y = obj_position.y - position.y + size.y + 0.1;
		}
		if (obj_position.y + obj_position.y < position.y) {
			res_velocity.y = position.y - obj_position.y - obj_size.y - 0.1;
		}
	}

	return res_velocity;
}

void RigidBody::move(TileMap* TM) {
	//Todo init:
	float vmax = 1.25;

	velocity -= velocity * friction;
	if (math.Length(velocity) < vmax) {
		velocity += acceleration / mass;
	}
	velocity = TM->collide(position, size, velocity, collision);
	//TODO:: other objects;

	position += velocity;
}