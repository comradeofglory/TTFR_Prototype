#include "Level.h"
#include "GMath.h"


void Level::init(std::string tile_map_file) {
	tile_map.init(tile_map_file);
	Texture text;
	text.loadFromFile("/Character/C1.png");
	player.init({ 128, 448 }, {32, 32});
	b.init({ 192, 512 }, { 16,16 }, 3);
	Character e1;
	e1.init({ 192, 512 }, { 16,16 });
	enemies.push_back(e1);
	// Тут могла быть ваша подгрузка персонажей из файла уровня
}

void Level::logic() {
	player.move(&tile_map, this);
}