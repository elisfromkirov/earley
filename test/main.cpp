#include <earley/recognizer.hpp>

#include <iostream>

int main() {
  Grammar grammar{
      Rule{'S', "U"},
      std::vector<Rule>{Rule{'U', "UU"}, Rule{'U', ""}, Rule{'U', "(U)"}}};

  EarleyRecognizer recognizer{grammar};

  std::cout << std::boolalpha;

  std::cout << recognizer.Recognize("()") << std::endl;
  std::cout << recognizer.Recognize("()()") << std::endl;
  std::cout << recognizer.Recognize("()(()())") << std::endl;
  std::cout << recognizer.Recognize("()((()))()") << std::endl;
  std::cout << recognizer.Recognize("(())()(())") << std::endl;

  std::cout << recognizer.Recognize("(") << std::endl;
  std::cout << recognizer.Recognize("(()))") << std::endl;
  std::cout << recognizer.Recognize("(())())") << std::endl;
  std::cout << recognizer.Recognize("())((((") << std::endl;
  std::cout << recognizer.Recognize("((()))(()") << std::endl;

  return 0;
}