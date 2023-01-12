#pragma once

#include <earley/grammar.hpp>
#include <earley/item.hpp>
#include <earley/item_set.hpp>

class EarleyRecognizer {
 public:
  explicit EarleyRecognizer(Grammar& grammar);

  [[nodiscard]] bool Recognize(const String& string) noexcept;

 private:
  void Scan(size_t right) noexcept;

  bool Predict(size_t right) noexcept;

  bool Complete(size_t right) noexcept;

 private:
  const String* string_;
  std::vector<ItemSet> sets_;
  Grammar& grammar_;
};
