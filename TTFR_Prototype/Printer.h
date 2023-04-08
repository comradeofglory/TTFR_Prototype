#pragma once
#include "Level.h"
#include "SFML/Graphics.hpp"
using namespace sf;

class Printer
{
private:
//	Vector2i window_size;
	RenderWindow* window;
	Level* level;
public:
	Printer(RenderWindow* _window, Level* _level);
	void draw();
};

