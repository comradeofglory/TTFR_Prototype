#pragma once
#include <SFML/Graphics.hpp>
#include "Character.h"
using namespace sf;

class CharacterMaster
{
private:
public:
	short int character_num;
	Character* character_list = new Character[character_num];

	void init();
};

