#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
#include "TileMap.h"

#define map_file "LevelInfo\\TypeMapping.txt"

/*
   Формат используемых файлов:
   файл уровня:
       целое число - количество используемых типов файлов
       перечисление используемых типов
       два целых числа - количество тайлов (по горизонтали и вертикали соотв.)
       перечесление типов тайлов по порядку (слева направо, сверху вниз)
   файл разметки типов:
       строки, в них последовательно номер типа, его уровень коллизии, путь до директории с его спрайтами
*/


//разбивает строку s в массив подстрок, разделенных по c
std::vector<std::string> split(std::string s, char c = ' ') {
    std::vector<std::string> res;
    std::string sub;
    std::stringstream ss(s);
    while (getline(ss, sub, ' ')) {
        res.push_back(sub);
    }
    return res;
}

int TileMap::index_search(int index) {
    int res = -1;
    if (type) {
        for (int i = 0; i < tile_type_number; i++) {
            if (index == type[i].type) {
                res = i;
            }
        }
    }
    return res;
}

/*подгружает текстуры в оперативную память вместе с коллизиями
    curr_text - текующий инициализируемый тип
    type - тип, по которму осуществляем поиск в словаре
    mapping_file - файл-словарь
*/
void load_textures(TileMap::tile_type* curr_type, int type, std::ifstream* mapping_file) {
    if (mapping_file) {
        std::string line;
        while (getline(*mapping_file, line)) {
            std::string curr_type_num = line.substr(0, line.find(' '));
            if (type == stoi(curr_type_num)) {
                std::vector<std::string> splitted_line = split(line);
                curr_type->type = type;
                curr_type->collision = (short int)stoi(splitted_line[1]);
                curr_type->texture = new Texture[std::distance(std::filesystem::directory_iterator(splitted_line[2]), {})];
                int i = 0;
                for (const auto& entry : std::filesystem::directory_iterator(splitted_line[2])) {
                    curr_type->texture[i].loadFromFile(entry.path().u8string());
                    i++;
                }
                break;
            }
        }
        (*mapping_file).seekg(0, std::ios::beg);
    }
}

void TileMap::init(std::string LevelFile) {
    int type_num = 0;
    
    int* used_type_indexes = NULL;

    std::ifstream load_f;
    load_f.open(LevelFile);

    load_f >> tile_type_number;
    type = new tile_type[tile_type_number];
    used_type_indexes = new int[type_num];

    for (int i = 0; i < type_num; i++) {
        load_f >> used_type_indexes[i];
    }

    load_f.close();

    std::ifstream mapping_file(map_file);

    for (int i = 0; i < type_num; i++) {
        load_textures(&(type[i]), used_type_indexes[i], &mapping_file);
    }

    mapping_file.close();

    std::ifstream load_f(LevelFile);

    load_f >> size.x >> size.y;

    tile = new tiles[size.x * size.y];

    for (int i = 0; i < size.y; i++) {
        for (int j = 0; j < size.x; j++) {
            load_f >> tile[j + i * size.y].tile_type;
            tile[j + i * size.y].t_position = Vector2i{j, i};
            tile[j + i * size.y].size = Vector2i{64, 64};                                                   //texture initialised by first texture in list
            tile[j + i * size.y].sprite.setTexture(type[index_search(tile[j + i * size.y].tile_type)].texture[0]);
        }
    }

}

TileMap::TileMap() {
    size = Vector2i{ 1, 2 };
}
