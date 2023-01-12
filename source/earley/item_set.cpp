#include <earley/item_set.hpp>

const std::vector<Item>& ItemSet::GetInfos() const noexcept {
  return items_;
}

bool ItemSet::HasItem(const Item& item) const noexcept {
  return std::any_of(items_.begin(), items_.end(),
                     [&desired_item = item](const Item& item) {
                       return desired_item.IsEqual(item);
                     });
}

bool ItemSet::AddItem(const Item& item) noexcept {
  if (HasItem(item)) {
    return false;
  }

  items_.push_back(item);
  return true;
}
