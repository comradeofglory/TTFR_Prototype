#include "Level.h"

void Level::init(std::string tile_map_file) {
	tile_map.init(tile_map_file);
	Texture text;
	text.loadFromFile("/Character/C1.png");
	player.init({ 80, 56 }, {8, 8});
	b.init({ 192, 512 }, { 16,16 }, 3);
}