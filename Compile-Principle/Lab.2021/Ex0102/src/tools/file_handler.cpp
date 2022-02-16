//
// Created by Holger on 2021/9/13.
//

#include "file_handler.h"

/**
 * @brief write strings to path
 */
int tools::write_result(const char *path, const std::string &result) {
  std::ofstream ofs(path, std::ios::out);
  if (!ofs.is_open()) {
    return 1;
  }
  ofs << result;
  ofs.close();
  return 0;
}

/**
 * @brief read strings from path
 */
int tools::read_data(const char *path, std::vector<std::string> &aim) {
  std::ifstream ifs(path, std::ios::in);
  if (!ifs.is_open()) {
    return 1;
  }
  std::string buffer;
  while (std::getline(ifs, buffer)) {
    aim.push_back(buffer);
  }
  ifs.close();
  return 0;
}
