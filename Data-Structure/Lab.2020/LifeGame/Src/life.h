//
// Created by holger on 2020/10/7.
//

#ifndef LIFE_GAME_LIFE_H
#define LIFE_GAME_LIFE_H

#include <cstring>
#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>

class Life {
public:
    static const std::string introduction;
    Life() : row(-1), col(-1) {}
    void initialize(std::istream &);
    void update();
    void show();
private:
    static const int max_row = 128;
    static const int max_col = 128;
    int grid[max_row + 2][max_col + 2]{};
    int row;
    int col;
    int count(int x, int y);
};

#endif //LIFE_GAME_LIFE_H
