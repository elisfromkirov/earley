#include <earley/grammar.hpp>

Rule::Rule(NonterminalSymbol nonterminal, String product) noexcept
    : nonterminal_{nonterminal},
      product_{std::move(product)} {
}

NonterminalSymbol Rule::GetNonterminal() const noexcept {
  return nonterminal_;
}

const String& Rule::GetProduct() const noexcept {
  return product_;
}

Grammar::Grammar(Rule start_rule, std::vector<Rule> rules) noexcept
    : start_rule_{std::move(start_rule)},
      rules_{std::move(rules)} {
}

Rule& Grammar::GetStartRule() noexcept {
  return start_rule_;
}

std::vector<Rule>& Grammar::GetRules() noexcept {
  return rules_;
}
