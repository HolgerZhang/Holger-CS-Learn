//
// Created by Holger on 2021/9/13.
//
#include "lexer.h"
#include "tools.h"

inline void test() {
  std::cout << lexer::Regex("ab(c|(dq)*)").get_ir() << std::endl;
  std::cout << lexer::Regex("ab(c|(dq)*)").parse() << std::endl;
  //(((((a)))))*
//  std::cout << lexer::Regex("a*").parse() << std::endl;
//  std::cout << lexer::Regex("(((((a)))))*").parse() << std::endl;
//  std::cout << lexer::Regex("a|b").parse() << std::endl;
//  std::cout << lexer::Regex("(a|(b)*cd)*").parse() << std::endl;
//  std::cout << lexer::Regex("(a|b)*(cd)*").parse() << std::endl;
//  std::cout << lexer::Regex("(a|b)d*(cd)*").parse() << std::endl;
//  std::cout << lexer::Regex("a|bdcd*").parse() << std::endl;
}

/**
 * @brief myt executable
 */
int main(int argc, const char **argv) {
//  test();

  tools::cmd_tool cmd{"myt", "MYT"};
  if (!tools::args_check(argc, argv, &cmd)) {
    return 1;
  }
  tools::show_info(&cmd);
  std::string input, result;
  std::vector<std::string> inputs;
  if (0 != tools::read_data(cmd.input_path, inputs)) {
    tools::loading_error(cmd.input_path);
    return 2;
  }
  if (1 != inputs.size()) {
    tools::exception("invalid input file format");
    return 3;
  }
  input = inputs.front();
  try {
    result = lexer::Regex(input).parse().to_string();
  } catch (std::runtime_error &e) {
    tools::exception(e);
    return 4;
  }
  if (0 != tools::write_result(cmd.output_path, result)) {
    tools::writing_error(cmd.output_path);
    return 5;
  }
  tools::success();
  return 0;
}

