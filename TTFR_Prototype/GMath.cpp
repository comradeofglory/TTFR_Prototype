#include "GMath.h"


sf::Vector2f Normalised(sf::Vector2f vector) {
	float mod = sqrt(vector.x * vector.x + vector.y * vector.y);
	if (mod == 0) {
		return { 0,0 };
	}
	return { vector.x / mod, vector.y / mod };
}

float Length(sf::Vector2f vector) {
	return sqrt(vector.x * vector.x + vector.y * vector.y);
}