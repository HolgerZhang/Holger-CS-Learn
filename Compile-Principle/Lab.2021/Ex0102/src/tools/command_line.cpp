//
// Created by Holger on 2021/9/15.
//

#include "command_line.h"

bool tools::args_check(int argc,
                       const char **argv,
                       struct cmd_tool *tool) {
  if (argc != 3) {
    std::cerr
        << "missing parameter: <input-file> and <output-file> is required!\n"
           "  usage: ./" << tool->tool_name << " <input-file> <output-file> "
        << std::endl;
    return false;
  }
  tool->input_path = argv[1], tool->output_path = argv[2];
  return true;
}

void tools::show_info(tools::cmd_tool *tool) {
  std::cout << "lexer-holger " << VER << " [" << tool->description << "]"
            << std::endl;
  std::cout << "  [input file] " << tool->input_path << std::endl;
  std::cout << "  [output file] " << tool->output_path << std::endl;
}

void tools::loading_error(const char *input_path) {
  std::cerr << "invalid input file path'" << input_path << "'" << std::endl;
}

void tools::writing_error(const char *output_path) {
  std::cerr << "invalid output file path'" << output_path << "'" << std::endl;
}

void tools::exception(const char *msg) {
  std::cerr << msg << std::endl;
}

void tools::exception(const std::runtime_error &e) {
  std::cerr << "catch an exception: " << e.what() << std::endl;
}

void tools::success() {
  std::cout << "result has been successfully written to the output file!"
            << std::endl;
}

