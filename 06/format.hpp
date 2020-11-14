#pragma once

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

size_t toSize_t(std::string_view num) {
  size_t result = 0;

  if (num.empty()) {
    throw std::invalid_argument("can't convert num.");
  }

  for (auto digit : num) {
    if (!isdigit(digit)) {
      throw std::invalid_argument("can't convert num.");
    }

    result = result * 10 + (digit - '0');
  }

  return result;
}

template <typename T>
std::string toString(const T& object) {
  std::stringstream result;
  result << object;
  return result.str();
}

template <typename... ArgsT>
std::string format(std::string_view str, const ArgsT&... args) {
  std::stringstream result;
  std::vector<std::string> arg = {toString(args)...};

  while (!str.empty()) {
    auto left = str.find('{');
    result << str.substr(0, left);
    if (left == str.npos) {
      break;
    }

    auto right = str.find('}');
    if (right == str.npos || right < left) {
      throw std::runtime_error("invalid scope seq.");
    }

    auto index_view = str.substr(left + 1, right - (left + 1));
    try {
      result << arg.at(toSize_t(index_view));
    } catch (const std::out_of_range&) {
      throw std::runtime_error("invalid args seq.");
    } catch (const std::invalid_argument&) {
      throw std::runtime_error("invalid index.");
    }

    str.remove_prefix(right + 1);
  }

  return result.str();
}
