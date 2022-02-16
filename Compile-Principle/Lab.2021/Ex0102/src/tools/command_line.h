//
// Created by Holger on 2021/9/15.
//

#include <iostream>

#ifndef LEXER_HOLGER_TOOLS_COMMAND_LINE_H_
#define LEXER_HOLGER_TOOLS_COMMAND_LINE_H_

#define VER "21.09.15"

namespace tools {

struct cmd_tool {
  const char *tool_name;
  const char *description;
  const char *input_path;
  const char *output_path;
};

bool args_check(int argc, const char **argv, struct cmd_tool *tool);
void show_info(struct cmd_tool *tool);
void loading_error(const char *input_path);
void writing_error(const char *output_path);
void success();
void exception(const char *msg);
void exception(const std::runtime_error &e);

}

#endif //LEXER_HOLGER_TOOLS_COMMAND_LINE_H_
