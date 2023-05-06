#include "RigidBody.h"
#include <string>
#include <fstream>

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

//Принимает RigidBody некоего другого объекта
//Меняет скорость аргумента
bool RigidBody::collide(RigidBody* other_rb) {
	bool res = 0;

	Vector2f obj_size = other_rb->size;
	Vector2f obj_position = other_rb->position;
	Vector2f obj_new_position = other_rb->position + other_rb->velocity;
	Vector2f obj_speed = other_rb->velocity;
	int obj_collision = other_rb->collision;

	Vector2f res_velocity = obj_speed;

	if (obj_collision > collision) {
		return res;
	}

	if (!(
		obj_new_position.x > position.x + size.x ||
		obj_new_position.x + obj_size.x < position.x ||
		obj_new_position.y > position.y + size.y ||
		obj_new_position.y + obj_size.y < position.y
		)) {
		res_velocity.x = 0;
		res_velocity.y = 0;
		res = 1;
	}
	
	//if (obj_position.x + obj_speed.x < position.x + size.x &&
	//	obj_position.x + obj_speed.x + obj_size.x > position.x &&
	//	obj_position.y < position.y + size.y &&
	//	obj_position.y + obj_size.y > position.y)
	//{
	//	res_velocity.x = 0;
	//	//TODO: interpolation
	//	if (obj_position.x > position.x + size.x) {
	//		res_velocity.x = obj_position.x - position.x + size.x + 0.1;
	//	}
	//	if (obj_position.x + obj_position.x < position.x) {
	//		res_velocity.x = position.x - obj_position.x - obj_size.x - 0.1;
	//	}
	//	//dbg
	//	res = 1;
	//}
	//if (obj_position.x < position.x + size.x &&
	//	obj_position.x + obj_size.x > position.x &&
	//	obj_position.y + obj_speed.y < position.y + size.y &&
	//	obj_position.y + obj_speed.y + obj_size.y > position.y)
	//{
	//	res_velocity.y = 0;
	//	//TODO: interpolation
	//	if (obj_position.y > position.y + size.y) {
	//		res_velocity.y = obj_position.y - position.y + size.y + 0.1;
	//	}
	//	if (obj_position.y + obj_position.y < position.y) {
	//		res_velocity.y = position.y - obj_position.y - obj_size.y - 0.1;
	//	}
	//	//dbg
	//	res = 1;
	//}
	
	other_rb->velocity = res_velocity;
	return res;
}

void RigidBody::move(TileMap* TM, std::vector<RigidBody*> enem_bodies) {
	//Todo init:
	float vmax = 10;

	velocity -= velocity * friction;
	if (Length(velocity) < vmax) {
		velocity += acceleration / mass;
	}

	velocity = TM->collide(position, size, velocity, collision);
	
	for (short int i = 0; i < enem_bodies.size(); i++) {
		(*enem_bodies[i]).collide(this);
	}

	//TODO:: other objects;
	position += velocity;
}
