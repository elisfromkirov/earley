#include <earley/recognizer.hpp>

#include <iostream>

EarleyRecognizer::EarleyRecognizer(Grammar& grammar)
    : grammar_{grammar} {
}

bool EarleyRecognizer::Recognize(const String& string) const noexcept {
  std::vector<ItemSet> sets(string.size() + 1);

  sets[0].AddItem(Item{grammar_.GetStartRule(), 0, 0});

  while (Predict(string, sets, 0) || Complete(string, sets, 0)) {
  }

  sets[0].Dump();

  for (size_t right = 0; right < string.size(); ++right) {
    std::cout << "right:" << right << std::endl;
    std::cout << std::endl;

    Scan(string, sets, right);

    sets[right + 1].Dump();

    while (Predict(string, sets, right + 1) ||
           Complete(string, sets, right + 1)) {
    }

    sets[right + 1].Dump();
  }

  return sets[string.size()].HasItem(Item{
      grammar_.GetStartRule(), grammar_.GetStartRule().GetProduct().size(), 0});
}

void EarleyRecognizer::Scan(const String& string, std::vector<ItemSet>& sets,
                            size_t right) const noexcept {
  for (const auto& info : sets[right].GetInfos()) {
    if (info.item.IsCompleted()) {
      continue;
    }

    std::cout << string[right] << info.item.GetCurrentSymbol() << std::endl;

    if (string[right] == info.item.GetCurrentSymbol()) {
      //      std::cout << info.parents.empty() << std::endl;
      sets[right + 1].AddItem(
          Item{info.item.GetRule(), info.item.GetPosition() + 1,
               info.item.GetLeft()},
          info.parents);
    }
  }

  std::cout << std::endl;
}

bool EarleyRecognizer::Predict(const String& string, std::vector<ItemSet>& sets,
                               size_t right) const noexcept {
  bool sets_changed = false;
  const auto& infos = sets[right].GetInfos();
  for (size_t i = 0; i < infos.size(); ++i) {
    if (infos[i].item.IsCompleted()) {
      continue;
    }

    for (const auto& rule : grammar_.GetRules()) {
      if (rule.GetNonterminal() == infos[i].item.GetCurrentSymbol()) {
        if (sets[right].AddItem(Item{rule, 0, right}, infos[i].item)) {
          sets_changed = true;
        }
      }
    }
  }
  return sets_changed;
}

bool EarleyRecognizer::Complete(const String& string,
                                std::vector<ItemSet>& sets,
                                size_t right) const noexcept {
  bool sets_changed = false;
  const auto& infos = sets[right].GetInfos();
  for (size_t i = 0; i < infos.size(); ++i) {
    if (!infos[i].item.IsCompleted()) {
      continue;
    }

    const auto& parent_infos = sets[infos[i].item.GetLeft()].GetInfos();
    for (size_t j = 0; j < parent_infos.size(); ++j) {
      if (parent_infos[j].item.IsCompleted()) {
        continue;
      }

      if (infos[i].item.GetRule().GetNonterminal() ==
          parent_infos[j].item.GetCurrentSymbol()) {
        if (sets[right].AddItem(Item{parent_infos[j].item.GetRule(),
                                     parent_infos[j].item.GetPosition() + 1,
                                     parent_infos[j].item.GetLeft()})) {
          sets_changed = true;
        }
      }
    }
  }
  return sets_changed;
}
