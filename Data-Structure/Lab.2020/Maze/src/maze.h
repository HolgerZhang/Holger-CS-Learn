// Project: Maze  File: maze.h
// Created by holger on 2021/1/3.

#include <iostream>
#include <fstream>
#include <utility>
#include <string>

#ifndef MAZE__MAZE_H_
#define MAZE__MAZE_H_

#define MAZE_WIDTH  8
#define MAZE_HEIGHT 8
#define MAZE_PATH   '0'
#define MAZE_WALL   '1'
#define MAZE_DEAD   '#'
#define MAZE_RESULT '*'

using std::istream;
using std::ostream;

/**
 * Maze Class
 */
class Maze {
 public:
  Maze(): walked_(false), found_(false) { }
  explicit Maze(bool from_file);
  void initialize(bool from_file = false);
  void show(ostream &output) const;
  bool walk();

 private:
  using Point = std::pair<int, int>;
  char maze_[MAZE_HEIGHT + 2][MAZE_WIDTH + 2]{};
  bool walked_;
  bool found_;
  void setup(istream &input);
  bool do_walk(const Point &point);
};

#endif //MAZE__MAZE_H_
