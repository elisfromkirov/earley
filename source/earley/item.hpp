#pragma once

#include <earley/grammar.hpp>

class Item {
 public:
  Item(const Rule& rule, size_t position, size_t left) noexcept;

  [[nodiscard]] const Rule& GetRule() const noexcept;

  [[nodiscard]] size_t GetPosition() const noexcept;

  [[nodiscard]] size_t GetLeft() const noexcept;

  [[nodiscard]] Symbol GetCurrentSymbol() const noexcept;

  [[nodiscard]] bool IsCompleted() const noexcept;

  [[nodiscard]] bool IsEqual(const Item& item) const noexcept;

 private:
  const Rule& rule_;
  size_t position_;
  size_t left_;
};
