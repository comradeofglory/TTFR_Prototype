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
                int i = 0;
                for (const auto& entry : std::filesystem::directory_iterator(splitted_line[2])) {
                    i++;
                }
                curr_type->texture = new Texture[i];
                i = 0;
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
    int* used_type_indexes = NULL;

    std::ifstream load_f;
    load_f.open(LevelFile);

    load_f >> tile_type_number;
    type = new tile_type[tile_type_number];
    used_type_indexes = new int[tile_type_number];

    for (int i = 0; i < tile_type_number; i++) {
        load_f >> used_type_indexes[i];
    }

    //load_f.close();

    std::ifstream mapping_file(map_file);

    for (int i = 0; i < tile_type_number; i++) {
        load_textures(&(type[i]), used_type_indexes[i], &mapping_file);
    }

    mapping_file.close();

    //load_f.open(LevelFile);

    load_f >> size.x >> size.y;

    tile = new tiles[size.x * size.y];
    
    for (int i = 0; i < size.y; i++) {
        for (int j = 0; j < size.x; j++) {
            load_f >> tile[j + i * size.x].tile_type;
            tile[j + i * size.x].t_position = Vector2i{ j, i };
            tile[j + i * size.x].collision = type[index_search(tile[j + i * size.x].tile_type)].collision;
            tile[j + i * size.x].size = Vector2i{8, 8};                                                   //texture initialised by first texture in list
            //tile[j + i * size.x].sprite.setTexture(type[index_search(tile[j + i * size.x].tile_type)].texture[0]);
            tile[j + i * size.x].sprite.setPosition({(float) j * tile[j + i * size.x].size.x,(float) i * tile[j + i * size.x].size.y});
        }
    }
    /*
Компоновка стен:
ggg
w0w   
ggg   

gwg ggg gwg
g1g g2g g3g
gwg gwg ggg

компоновка полов:
rand%4
*/

    for (int i = 0; i < size.y; i++) {
        for (int j = 0; j < size.x; j++) {
            int t = 0;
            if (tile[j + i * size.x].tile_type == 1) {
                t = rand() % 4;
            }
            if (tile[j + i * size.x].tile_type == 2) {
                if (i < size.y && tile[j + (i + 1) * size.x].tile_type == 2) {
                    t = 2;
                }
                if (i > 0 && tile[j + (i - 1) * size.x].tile_type == 2) {
                    if (t == 2) {
                        t = 1;
                    }
                    else {
                        t = 3;
                    }
                }
            }
            tile[j + i * size.x].sprite.setTexture(type[index_search(tile[j + i * size.x].tile_type)].texture[t]);
        }
    }
    
}

TileMap::TileMap() {
    size = Vector2i{ 1, 2 };
}

// Коллизия и связанные с ней функции

//Перевод Абсолютных координат в координаты тайлмепа

Vector2i TileMap::get_TM_position(Vector2f abs_position) {
    int x, y;
    x = abs_position.x / tile[0].size.x;
    y = abs_position.y / tile[0].size.y;
    return { x, y };
}

//Получение коллизии тайла по координатам

int TileMap::get_tile_collision(Vector2i TM_position) {
    return tile[TM_position.y * size.x + TM_position.x].collision;
}



//  Точки объекта
//  0-----1
//  |     |
//  |     |
//  2-----3


Vector2f TileMap::collide(Vector2f char_position, Vector2f char_size, Vector2f char_velocity, short int char_collision) {
    Vector2f res_velocity = char_velocity;

    std::vector<Vector2f> dots;
    
    //в определении числа точек на границе тела исходил из того, что все тайлы равны по размеру, при том квадратные
    //это позволило просто поделить на ширину первого тайла
    int dots_on_x = ceil(char_size.x / (tile[0].size.x - 1));
    float x_delta = char_size.x / dots_on_x;
    int dots_on_y = ceil(char_size.y / (tile[0].size.y - 1));
    float y_delta = char_size.y / dots_on_y;

    for (int i = 0; i < dots_on_x; i++) {
        dots.push_back(Vector2f{ char_position.x + x_delta * i, char_position.y });
    }

    for (int i = 0; i < dots_on_y; i++) {
        dots.push_back(Vector2f{ char_position.x + char_size.x, char_position.y + y_delta*i});
    }

    for (int i = 0; i < dots_on_x; i++) {
        dots.push_back(Vector2f{ char_position.x + char_size.x - x_delta * i, char_position.y + char_size.y});
    }

    for (int i = 0; i < dots_on_x; i++) {
        dots.push_back(Vector2f{ char_position.x, char_position.y + char_size.y - y_delta*i});
    }


    Vector2f new_dot[2];
    for (int i = 0; i < dots.size(); i++) {
        new_dot[0] = dots[i];
        new_dot[0].x += char_velocity.x;
        new_dot[1] = dots[i];
        new_dot[1].y += char_velocity.y;

        //TODO: Проверять только те точки, которые необход

        if (char_collision <= get_tile_collision(get_TM_position(new_dot[0]))) {
            res_velocity.x = 0;
            //интерполяция
            res_velocity.x = (float)get_TM_position(new_dot[0]).x * tile[0].size.x - dots[i].x;
           
            if (dots[i].x > (float)get_TM_position(new_dot[0]).x * tile[0].size.x) {
                res_velocity.x += tile[0].size.x;
            }
            
            if (res_velocity.x > 0) {
                res_velocity.x -= 0.1;
            }
            else if (res_velocity.x < 0) {
                res_velocity.x += 0.1;
            }
        }
        if (char_collision <= get_tile_collision(get_TM_position(new_dot[1]))) {
            res_velocity.y = 0;
            //интерполяция
            res_velocity.y = (float)get_TM_position(new_dot[0]).y * tile[0].size.y - dots[i].y;

            if (dots[i].y > ((float)get_TM_position(new_dot[0]).y + 0.5) * tile[0].size.y) {
                res_velocity.y += tile[0].size.y;
            }

            if (res_velocity.y > 0) {
                res_velocity.y -= 0.01;
            }
            else if (res_velocity.y < 0) {
                res_velocity.y += 0.01;
            }
        }
    }

    return res_velocity;
}
