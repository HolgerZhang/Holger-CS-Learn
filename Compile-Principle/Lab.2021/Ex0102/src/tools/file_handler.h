//
// Created by Holger on 2021/9/13.
//

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#ifndef LEXER_HOLGER_TOOLS_FILE_HANDLER_H_
#define LEXER_HOLGER_TOOLS_FILE_HANDLER_H_

namespace tools {

int write_result(const char *path, const std::string &result);
int read_data(const char *path, std::vector<std::string> &aim);

}

#endif //LEXER_HOLGER_TOOLS_FILE_HANDLER_H_
