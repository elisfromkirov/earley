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

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}