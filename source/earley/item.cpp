#include <earley/item.hpp>

Item::Item(const Rule& rule, size_t position, size_t left) noexcept
    : rule_{rule},
      position_{position},
      left_{left} {
}

const Rule& Item::GetRule() const noexcept {
  return rule_;
}

size_t Item::GetPosition() const noexcept {
  return position_;
}

size_t Item::GetLeft() const noexcept {
  return left_;
}

Symbol Item::GetCurrentSymbol() const noexcept {
  return rule_.GetProduct()[position_];
}

bool Item::IsCompleted() const noexcept {
  return position_ == rule_.GetProduct().size();
}

bool Item::IsEqual(const Item& item) const noexcept {
  return rule_.GetNonterminal() == item.rule_.GetNonterminal() &&
         rule_.GetProduct() == item.rule_.GetProduct() &&
         position_ == item.position_ &&
         left_ == item.left_;
}
