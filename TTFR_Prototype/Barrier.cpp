#include "Barrier.h"

void Barrier::init(Vector2f position, Vector2f size, int collision) {
	body.init(size, position, collision);
	shape.setFillColor(Color::Red);
	shape.setPosition(position);
	shape.setSize(size);
}