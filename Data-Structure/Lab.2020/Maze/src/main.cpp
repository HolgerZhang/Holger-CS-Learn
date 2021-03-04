#include <iostream>
#include <string>
#include "maze.h"

using std::cout;

char welcome[] = "Welcome to Maze solution. Author: Zhang Hao\n"
                 "You can input the maze or generate it randomly (using python script 'generator.py' in advance).\n"
                 "It is a 0-1 matrix of 8 rows and 8 columns, with each number separated by a space.\n"
                 "\"0\" is the access path and \"1\" is the wall.\n"
                 "The program will judge whether it can go from the beginning(left-up) to the end(right-down).\n"
                 "If it can, it will show you a path out of the maze.\n"
                 "\"*\" means the access path, \"#\" is the dead end.\n";

int main() {
  cout << welcome << std::endl;
  cout << "Do you want to input the maze manually? [Y/n]";
  std::string cmd;
  std::getline(std::cin, cmd);
  Maze maze(!cmd.empty() && !(cmd[0] == 'Y' || cmd[0] == 'y'));
  cout << "The origin maze is: \n";
  maze.show(std::cout);
  if (maze.walk()) {
    cout << "The problem solved, solution is: \n";
  } else {
    cout << "There is no solution to the problem, attempted path is: \n";
  }
  maze.show(std::cout);
  return 0;
}
