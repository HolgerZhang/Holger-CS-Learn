//
// Created by Holger on 2021/9/13.
//
#include "lexer.h"
#include "tools.h"

inline void test() {
  auto nfa = lexer::Regex("(a|b)*abb").parse();
  std::cout << nfa << std::endl;
  auto dfa = nfa.subset_construction();
  std::cout << dfa << std::endl;
//  auto nfa = lexer::NFA({"1 a 2", "2 b 3", "...: 1", "..: 2 3"});
//  std::cout << nfa.subset_construction() << std::endl;
}

/**
 * @brief subset executable
 */
int main(int argc, const char **argv) {
//  test();

  tools::cmd_tool cmd{"subset-construction", "Subset Construction"};
  if (!tools::args_check(argc, argv, &cmd)) {
    return 1;
  }
  tools::show_info(&cmd);
  std::vector<std::string> input;
  if (0 != tools::read_data(cmd.input_path, input)) {
    tools::loading_error(cmd.input_path);
    return 2;
  }
  lexer::NFA nfa(input);
  lexer::DFA dfa = nfa.subset_construction();
  if (0 != tools::write_result(cmd.output_path, dfa.to_string())) {
    tools::writing_error(cmd.output_path);
    return 3;
  }
  tools::success();
  return 0;
}