#include <earley/recognizer.hpp>

#include <gtest/gtest.h>

TEST(EarleyRecognizer, CorrectBracketSequence) {
  Grammar grammar{
      Rule{'S', "U"},
      std::vector<Rule>{Rule{'U', "UU"}, Rule{'U', ""}, Rule{'U', "(U)"}}};

  EarleyRecognizer recognizer{grammar};

  EXPECT_TRUE(recognizer.Recognize("()"));
  EXPECT_TRUE(recognizer.Recognize("()()"));
  EXPECT_TRUE(recognizer.Recognize("()(()())"));
  EXPECT_TRUE(recognizer.Recognize("()((()))()"));
  EXPECT_TRUE(recognizer.Recognize("(())()(())"));
}

TEST(EarleyRecognizer, IncorrectBracketSequence) {
  Grammar grammar{
      Rule{'S', "U"},
      std::vector<Rule>{Rule{'U', "UU"}, Rule{'U', ""}, Rule{'U', "(U)"}}};

  EarleyRecognizer recognizer{grammar};

  EXPECT_FALSE(recognizer.Recognize("("));
  EXPECT_FALSE(recognizer.Recognize("(()))"));
  EXPECT_FALSE(recognizer.Recognize("(())())"));
  EXPECT_FALSE(recognizer.Recognize("())(((("));
  EXPECT_FALSE(recognizer.Recognize("((()))(()"));
}

TEST(EarleyRecognizer, CorrectArithmeticExpression) {
  Grammar grammar{
      Rule{'S', "E"},
      std::vector<Rule>{
          Rule{'E', "E+T"}, Rule{'E', "E-T"}, Rule{'E', "T"}, Rule{'T', "T*F"},
          Rule{'T', "T/F"}, Rule{'T', "F"}, Rule{'F', "0"}, Rule{'F', "1"},
          Rule{'F', "2"}, Rule{'F', "3"}, Rule{'F', "4"}, Rule{'F', "5"},
          Rule{'F', "6"}, Rule{'F', "7"}, Rule{'F', "8"}, Rule{'F', "9"}}};

  EarleyRecognizer recognizer{grammar};

  EXPECT_TRUE(recognizer.Recognize("7-5"));
  EXPECT_TRUE(recognizer.Recognize("7-5*5"));
  EXPECT_TRUE(recognizer.Recognize("6*7-5/5"));
  EXPECT_TRUE(recognizer.Recognize("1-3*5+5*4*5*5+5"));
  EXPECT_TRUE(recognizer.Recognize("0+1+2+3+4+5-6-7-8-9"));
}

TEST(EarleyRecognizer, IncorrectArithmeticExpression) {
  Grammar grammar{
      Rule{'S', "E"},
      std::vector<Rule>{
          Rule{'E', "E+T"}, Rule{'E', "E-T"}, Rule{'E', "T"}, Rule{'T', "T*F"},
          Rule{'T', "T/F"}, Rule{'T', "F"}, Rule{'F', "0"}, Rule{'F', "1"},
          Rule{'F', "2"}, Rule{'F', "3"}, Rule{'F', "4"}, Rule{'F', "5"},
          Rule{'F', "6"}, Rule{'F', "7"}, Rule{'F', "8"}, Rule{'F', "9"}}};

  EarleyRecognizer recognizer{grammar};

  EXPECT_FALSE(recognizer.Recognize("7--5"));
  EXPECT_FALSE(recognizer.Recognize("*5*"));
  EXPECT_FALSE(recognizer.Recognize("3+*2"));
  EXPECT_FALSE(recognizer.Recognize("5/3-0+4*3**4"));
  EXPECT_FALSE(recognizer.Recognize("1-3*5+5**4*5*5+5"));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}