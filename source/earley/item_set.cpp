#include <earley/item_set.hpp>

const std::vector<ItemSet::ItemInfo>& ItemSet::GetInfos() const noexcept {
  return infos_;
}

bool ItemSet::HasItem(const Item& item) const noexcept {
  return std::any_of(infos_.begin(), infos_.end(), [&](const ItemInfo& info) {
    return item.IsEqual(info.item);
  });
}

bool ItemSet::AddItem(const Item& item) noexcept {
  if (HasItem(item)) {
    return false;
  }

  infos_.push_back(ItemInfo{item, std::vector<Item>{}});
  return true;
}

bool ItemSet::AddItem(const Item& item, const Item& parent) noexcept {
  for (size_t i = 0; i < infos_.size(); ++i) {
    if (!item.IsEqual(infos_[i].item)) {
      continue;
    }
    for (size_t j = 0; j < infos_[i].parents.size(); ++j) {
      if (parent.IsEqual(infos_[i].parents[j])) {
        return false;
      }
    }
    infos_[i].parents.push_back(parent);
    return true;
  }

  infos_.push_back(ItemInfo{item, std::vector<Item>{parent}});
  return true;
}

bool ItemSet::AddItem(const Item& item,
                      const std::vector<Item>& parents) noexcept {
  for (size_t i = 0; i < infos_.size(); ++i) {
    if (!item.IsEqual(infos_[i].item)) {
      continue;
    }

    bool added = false;
    for (const auto& parent : parents) {
      for (size_t j = 0; j < infos_[i].parents.size(); ++j) {
        if (parent.IsEqual(infos_[i].parents[j])) {
          continue;
        }
      }
      infos_[i].parents.push_back(parent);
      added = true;
    }
    if (!added) {
      return false;
    }
  }

  infos_.push_back(ItemInfo{item, parents});
  return true;
}
