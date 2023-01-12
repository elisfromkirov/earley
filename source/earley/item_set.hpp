#pragma once

#include <earley/item.hpp>

#include <vector>

#include <iostream>

class ItemSet {
 public:
  [[nodiscard]] const std::vector<Item>& GetInfos() const noexcept;

  [[nodiscard]] bool HasItem(const Item& item) const noexcept;

  bool AddItem(const Item& item) noexcept;

 private:
  std::vector<Item> items_;
};
