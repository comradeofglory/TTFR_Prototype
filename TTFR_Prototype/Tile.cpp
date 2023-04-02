#include "Tile.h"

void Tile::init(Vector2i start_tile_position, Vector2i start_size, short int _collision, short int _animation_num, Texture* _texture) {
	tile_position = start_tile_position;
	size = start_size;
	position.x = tile_position.x * size.x;
	position.y = tile_position.y * size.y;
	collision = _collision;
	animation_num = _animation_num;
	text = _texture;
}

void Tile::animation_play(int  animation_speed, int frame_num) {
	if (frame_num % animation_speed) {
		if (animation_count < animation_num) {
			animation_count++;
		}
		else {
			animation_count = 0;
		}

		sprite.setTexture(text[animation_count]);			//Меняем спрайт
	}
}