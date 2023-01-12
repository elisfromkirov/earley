#pragma once

#include <earley/item.hpp>

#include <vector>

#include <iostream>

class ItemSet {
 public:
  struct ItemInfo {
    Item item;
    std::vector<Item> parents;
  };

 public:
  const std::vector<ItemInfo>& GetInfos() const noexcept;

  bool HasItem(const Item& item) const noexcept;

  bool AddItem(const Item& item) noexcept;

  bool AddItem(const Item& item, const Item& parent) noexcept;

  bool AddItem(const Item& item, const std::vector<Item>& parents) noexcept;

  void Dump() {
    for (size_t i = 0; i < infos_.size(); ++i) {
      std::cout << "[";
      std::cout << infos_[i].item.GetRule().GetNonterminal();
      std::cout << "->";
      for (size_t j = 0; j < infos_[i].item.GetPosition(); ++j) {
        std::cout << infos_[i].item.GetRule().GetProduct()[j];
      }
      std::cout << ".";
      for (size_t j = infos_[i].item.GetPosition();
           j < infos_[i].item.GetRule().GetProduct().size(); ++j) {
        std::cout << infos_[i].item.GetRule().GetProduct()[j];
      }
      std::cout << ", ";
      std::cout << infos_[i].item.GetLeft();
      std::cout << "] completed: ";
      std::cout << std::boolalpha << infos_[i].item.IsCompleted();
      std::cout << " parents: { ";
      for (const auto& parent : infos_[i].parents) {
        std::cout << "[";
        std::cout << parent.GetRule().GetNonterminal();
        std::cout << "->";
        for (size_t j = 0; j < parent.GetPosition(); ++j) {
          std::cout << parent.GetRule().GetProduct()[j];
        }
        std::cout << ".";
        for (size_t j = parent.GetPosition();
             j < parent.GetRule().GetProduct().size(); ++j) {
          std::cout << parent.GetRule().GetProduct()[j];
        }
        std::cout << ", ";
        std::cout << parent.GetLeft();
        std::cout << "] ";
      }
      std::cout << "}";
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }

 private:
  std::vector<ItemInfo> infos_;
};
