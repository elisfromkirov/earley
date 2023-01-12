#include <earley/recognizer.hpp>

#include <iostream>

EarleyRecognizer::EarleyRecognizer(Grammar& grammar)
    : string_{nullptr},
      sets_{},
      grammar_{grammar} {
}

bool EarleyRecognizer::Recognize(const String& string) noexcept {
  string_ = &string;
  sets_.resize(string.size() + 1);

  sets_[0].AddItem(Item{grammar_.GetStartRule(), 0, 0});
  while (Predict(0) || Complete(0)) {
  }

  for (size_t right = 0; right < string.size(); ++right) {
    Scan(right);

    while (Predict(right + 1) || Complete(right + 1)) {
    }
  }

  return sets_[string_->size()].HasItem(Item{
      grammar_.GetStartRule(), grammar_.GetStartRule().GetProduct().size(), 0});
}

void EarleyRecognizer::Scan(size_t right) noexcept {
  for (const auto& item : sets_[right].GetInfos()) {
    if (item.IsCompleted()) {
      continue;
    }

    if (string_->at(right) == item.GetCurrentSymbol()) {
      sets_[right + 1].AddItem(
          Item{item.GetRule(), item.GetPosition() + 1, item.GetLeft()});
    }
  }
}

bool EarleyRecognizer::Predict(size_t right) noexcept {
  bool sets_changed = false;
  const auto& items = sets_[right].GetInfos();
  for (size_t i = 0; i < items.size(); ++i) {
    if (items[i].IsCompleted()) {
      continue;
    }

    for (const auto& rule : grammar_.GetRules()) {
      if (rule.GetNonterminal() == items[i].GetCurrentSymbol()) {
        if (sets_[right].AddItem(Item{rule, 0, right})) {
          sets_changed = true;
        }
      }
    }
  }
  return sets_changed;
}

bool EarleyRecognizer::Complete(size_t right) noexcept {
  bool sets_changed = false;
  const auto& items = sets_[right].GetInfos();
  for (size_t i = 0; i < items.size(); ++i) {
    if (!items[i].IsCompleted()) {
      continue;
    }

    const auto& parent_items = sets_[items[i].GetLeft()].GetInfos();
    for (size_t j = 0; j < parent_items.size(); ++j) {
      if (parent_items[j].IsCompleted()) {
        continue;
      }

      if (items[i].GetRule().GetNonterminal() ==
          parent_items[j].GetCurrentSymbol()) {
        if (sets_[right].AddItem(Item{parent_items[j].GetRule(),
                                      parent_items[j].GetPosition() + 1,
                                      parent_items[j].GetLeft()})) {
          sets_changed = true;
        }
      }
    }
  }
  return sets_changed;
}
