#pragma once

#include <earley/grammar.hpp>
#include <earley/item.hpp>
#include <earley/item_set.hpp>

class EarleyRecognizer {
 public:
  explicit EarleyRecognizer(Grammar& grammar);

  [[nodiscard]] bool Recognize(const String& string) const noexcept;

 private:
  void Scan(const String& string, std::vector<ItemSet>& sets,
            size_t index) const noexcept;

  bool Predict(const String& string, std::vector<ItemSet>& sets,
               size_t index) const noexcept;

  bool Complete(const String& string, std::vector<ItemSet>& sets,
                size_t index) const noexcept;

 private:
  Grammar& grammar_;
};
