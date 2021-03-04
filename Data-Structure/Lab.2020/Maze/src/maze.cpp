// Project: Maze  File: maze.cpp
// Created by holger on 2021/1/3.

#include "maze.h"

Maze::Maze(bool from_file) : walked_(false), found_(false) {
  initialize(from_file);
}

void Maze::initialize(bool from_file) {
  for (int i = 0; i < MAZE_HEIGHT + 2; ++i) {
    maze_[i][0] = MAZE_WALL;
    maze_[i][MAZE_WIDTH + 1] = MAZE_WALL;
  }
  for (int i = 0; i < MAZE_WIDTH + 2; ++i) {
    maze_[0][i] = MAZE_WALL;
    maze_[MAZE_HEIGHT + 1][i] = MAZE_WALL;
  }
  if (from_file) {
    std::cout << "Do you want to generate maze now? [Y/n]";
    std::string cmd;
    std::getline(std::cin, cmd);
    if (!cmd.empty() && (cmd[0] == 'Y' || cmd[0] == 'y')) {
      system("python generator.py");
    }
    std::ifstream input("maze.init", std::ios::in);
    if (!input.is_open()) {
      std::cerr << "init file not found.\n";
      exit(1);
    }
    setup(input);
    input.close();
  } else {
    std::cout << "Now input the 8*8 Maze:\n";
    setup(std::cin);
  }
}

void Maze::setup(istream &input) {
  for (int i = 1; i <= MAZE_HEIGHT; ++i) {
    for (int j = 1; j <= MAZE_WIDTH; ++j) {
      int point;
      input >> point;
      if (point != 0 && point != 1) {
        std::cerr << "invalid maze.\n";
        exit(2);
      }
      maze_[i][j] = (point == 0) ? MAZE_PATH : MAZE_WALL;
    }
  }
}

void Maze::show(ostream &output) const {
  for (int i = 1; i <= MAZE_HEIGHT; ++i) {
    for (int j = 1; j <= MAZE_WIDTH; ++j) {
      output << maze_[i][j] << ' ';
    }
    output << std::endl;
  }
}

bool Maze::walk() {
  if (walked_) {
    std::cout << "The problem solved, call 'show()' to show the solution.\n";
    return found_;
  }
  found_ = do_walk({1, 1});
  return found_;
}

bool Maze::do_walk(const Point &point) {
  if (maze_[point.first][point.second] == MAZE_PATH) {
    maze_[point.first][point.second] = MAZE_RESULT;
    if (point.first == MAZE_HEIGHT && point.second == MAZE_WIDTH) {
      return true;
    }
    Point next[]{
        {point.first, point.second + 1},      // right
        {point.first + 1, point.second + 1},      // right-down
        {point.first + 1, point.second},      // down
        {point.first + 1, point.second - 1},      // left-down
        {point.first, point.second - 1},      // left
        {point.first - 1, point.second - 1},      // left-up
        {point.first - 1, point.second},      // up
        {point.first - 1, point.second + 1}      // right-up
    };
    int cnt = 0;
    for (const auto &item : next) {
      if (do_walk(item)) { return true; }
      else { cnt++; }
    }
    if (cnt >= 8) {
      maze_[point.first][point.second] = MAZE_DEAD;
    }
  }
  return false;
}
