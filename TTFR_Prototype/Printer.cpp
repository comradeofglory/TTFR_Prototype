#include "Printer.h"
#include "TileMap.h"

Printer::Printer(RenderWindow* _window, Level* _level) {
	window = _window;
	level = _level;
}

void Printer::draw() {
	window->clear(Color::Black);
	//TODO interface
	for (int i = 0; i < level->tile_map.size.x * level->tile_map.size.y; i++) {
		window->draw(level->tile_map.tile[i].sprite);
	}
	window->display();
}