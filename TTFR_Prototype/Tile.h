#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Tile
{
private:

public:
	Vector2i position, tile_position, size;			//�������, ������� � �.�. ��������, ������ �����
	short int collision;							//������� ��������
	short int animation_num;						//���������� ������ ��������
	short int animation_count;						//������� ���� ��������
	Sprite sprite;									//������
	Texture* text = new Texture[animation_num];		//�������� ���� ������ ��������

	void init(Vector2i start_tile_position, Vector2i start_size, short int _collision, short int _animation_num, Texture* _texture);
	void animation_play(int  animation_speed, int frame_num); 	//�������� ��������, ������� ����� ����� 
};

