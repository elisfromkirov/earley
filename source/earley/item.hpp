#pragma once

#include <earley/grammar.hpp>

class Item {
 public:
  Item(const Rule& rule, size_t position, size_t left) noexcept;

  const Rule& GetRule() const noexcept;

  size_t GetPosition() const noexcept;

  size_t GetLeft() const noexcept;

  Symbol GetCurrentSymbol() const noexcept;

  bool IsCompleted() const noexcept;

  bool IsEqual(const Item& item) const noexcept;

 private:
  const Rule& rule_;
  size_t position_;
  size_t left_;
};
