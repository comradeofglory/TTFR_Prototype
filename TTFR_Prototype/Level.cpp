#include "Level.h"
#include "GMath.h"

std::vector<RigidBody*> get_objects_info(std::vector<Character> enemies);


void Level::init(std::string tile_map_file) {
	tile_map.init(tile_map_file);
	player.init({ 128, 448 }, {32, 32}, 2);
	b.init({ 192, 512 }, { 16,16 }, 3);
	Character e1;
	e1.init({ 198, 448 }, {32, 32}, 3);
	enemies.push_back(e1);
	// Тут могла быть ваша подгрузка персонажей из файла уровня
}

void Level::logic() {

	std::vector<RigidBody*> res;
	for (short int i = 0; i < enemies.size(); i++) {
		res.push_back(&(enemies[i].body));
	}

	player.move(&tile_map, res);
}