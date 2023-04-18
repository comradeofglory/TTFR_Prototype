#include "StaticBody.h"

void StaticBody::init(Vector2f _size, Vector2f _position, int _collision) {
	size = _size;
	position = _position;
	collision = _collision;
}

Vector2f StaticBody::collide(Vector2f obj_size, Vector2f obj_position, Vector2f obj_speed, int obj_collision) {
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
				res_velocity.x =  position.x - obj_position.x - obj_size.x - 0.1;
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