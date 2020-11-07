#pragma once

#include <iostream>
#include <string>
#include <string_view>
#include <stdexcept>

#include "Vector.h"

void removeSpacesAround(std::string_view& view) {
  while (view.size() && isspace(view[0])) {
    view.remove_prefix(1);
  }

  while (view.size() && isspace(view.back())) {
    view.remove_suffix(1);
  }
}

int toInt(std::string_view view) {
  int num = 0;
  for (auto digit : view) {
    if (!isdigit(digit)) {
      throw std::invalid_argument("can't convert std::string_view to int.");
    }

    num = num * 10 + static_cast<int>(digit - '0');
  }

  return num;
}

bool parseAndRemoveSign(std::string_view& view) {
  bool is_negative = false;
  while (view.size() && (view[0] == '-' || view[0] == '+')) {
    if (view[0] == '-') {
      is_negative = !is_negative;
    }
    view.remove_prefix(1);
  }

  return is_negative;
}

Vector<int> parseRanks(std::string_view& view, const size_t RANK_LEN) {
  Vector<int> ranks;
  ranks.reserve(view.size() / RANK_LEN + 1);

  while (view.size()) {
    size_t rank_begin = RANK_LEN < view.size() ? view.size() - RANK_LEN : 0;
    auto rank_view = view.substr(rank_begin);

    ranks.push_back(toInt(rank_view));
    view.remove_suffix(rank_view.size());
  }

  while (ranks.size() && ranks.back() == 0) {
    ranks.pop_back();
  }

  return ranks;
}
