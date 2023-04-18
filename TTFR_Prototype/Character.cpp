#include "Character.h"

void Character::init(Vector2f position, Vector2f size) {
	body.init(position, size, 1, 0.18, 2);
	body.set_velocity({ 0.f,0.f });
	body.set_acceleration({ 0.f,0.f });
	shape.setFillColor(Color::White);
	shape.setPosition(position);
	shape.setSize(size);
}