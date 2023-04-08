#include "Character.h"

void Character::init(Vector2i _position, Vector2i _size, short int _collision, short int _animation_num, Texture* _text, State _animation_segment) {
	position = _position;
	size = _size;
	collision = _collision;
	animation_num = _animation_num;
	text = _text;
	animation_segment = _animation_segment;
}

void Character::move(TileMap tile_map) {
	velocity = tile_map.collide(position, size, velocity, collision);
	position += velocity;
}