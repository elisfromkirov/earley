#pragma once

#include <string>
#include <vector>

using TerminalSymbol = char;

using NonterminalSymbol = char;

using Symbol = char;

using String = std::string;

class Rule {
 public:
  Rule(NonterminalSymbol nonterminal, String product) noexcept;

  [[nodiscard]] NonterminalSymbol GetNonterminal() const noexcept;

  [[nodiscard]] const String& GetProduct() const noexcept;

 private:
  NonterminalSymbol nonterminal_;
  String product_;
};

class Grammar {
 public:
  Grammar(Rule start_rule, std::vector<Rule> rules) noexcept;

  Rule& GetStartRule() noexcept;

  std::vector<Rule>& GetRules() noexcept;

 private:
  Rule start_rule_;
  std::vector<Rule> rules_;
};