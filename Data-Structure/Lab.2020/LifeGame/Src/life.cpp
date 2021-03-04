//
// Created by holger on 2020/10/7.
//

#include "life.h"

const std::string Life::introduction =
        "Welcome to the game of Life.\n"
        "This game uses a grid of size 128*128.\n"
        "Each cell can either be occupied by an organism or not.\n"
        "The occupied cells change from generation to generation according to how many neighboring cells are alive.\n";

void Life::initialize(std::istream &in) {
    row = 0;
    col = 0;
    while (true) {
        std::string line;
        getline(in, line);
        if (line == "#" || in.eof()) {
            break;
        }
        if (col == 0) {
            if ((col = line.length()) > max_col) {
                throw std::out_of_range{"The number of column exceeded max size " + std::to_string(max_col)};
            }
        }
        if ((++row) > max_row) {
            throw std::out_of_range{"The number of row exceeded max size " + std::to_string(max_row)};
        }
        if (row > 1 && line.length() != col) {
            throw std::invalid_argument{"The configuration is not a rectangle"};
        }
        for (int j = 1; j <= col; ++j) {
            if (line[j - 1] == ' ') {
                grid[row][j] = 0;
            } else if (line[j - 1] == 'x') {
                grid[row][j] = 1;
            } else {
                throw std::invalid_argument{"An invalid character in the configuration"};
            }
        }
    }
}

void Life::update() {
    int new_grid[max_row][max_row]{};

    for (int i = 1; i <= row; ++i) {
        for (int j = 1; j <= col; ++j) {
            switch (count(i, j)) {
                case 2:   // keep still
                    new_grid[i][j] = grid[i][j];
                    break;
                case 3:    // alive
                    new_grid[i][j] = 1;
                    break;
                default:     // dead
                    new_grid[i][j] = 0;
            }
        }
    }

    for (int i = 1; i <= row; ++i) {
        for (int j = 1; j <= col; ++j) {
            grid[i][j] = new_grid[i][j];
        }
    }

}

void Life::show() {
    for (int i = 1; i <= row; ++i) {
        for (int j = 1; j <= col; ++j) {
            std::cout << (grid[i][j] == 0 ? ' ' : 'x');
        }
        std::cout << std::endl;
    }
}

int Life::count(int x, int y) {
    int num = 0;
    for (int i = x - 1; i <= x + 1; ++i) {
        for (int j = y - 1; j <= y + 1; ++j) {
            if (!(i == x && j == y) && grid[i][j] != 0) {
                num++;
            }
        }
    }
    return num;
}