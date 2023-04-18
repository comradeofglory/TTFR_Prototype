#include "Area.h"

bool Area::collide(Vector2f obj_position, Vector2f obj_size) {
	if (obj_position.x  < position.x + size.x &&
		obj_position.x + obj_size.x > position.x &&
		obj_position.y < position.y + size.y &&
		obj_position.y + obj_size.y > position.y)
	{
		return true;
	}
	else {
		return false;
	}
}