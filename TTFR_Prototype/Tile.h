#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Tile
{
private:

public:
	Vector2i position, tile_position, size;			//Позиция, позиция в с.к. Тайлмепа, размер тайла
	short int collision;							//Уровень коллизии
	short int animation_num;						//Количество кадров анимации
	short int animation_count;						//Текущий кадр анимации
	Sprite sprite;									//Спрайт
	Texture* text = new Texture[animation_num];		//Текстуры всех кадров анимации

	void init(Vector2i start_tile_position, Vector2i start_size, short int _collision, short int _animation_num, Texture* _texture);
	void animation_play(int  animation_speed, int frame_num); 	//Скорость анимации, текущий номер кадра 
};

