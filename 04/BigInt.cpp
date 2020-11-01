#include "BigInt.h"

#include <iomanip>
#include <stdexcept>
#include <string_view>
#include <vector>

BigInt::BigInt(const std::string& number) {
  std::string_view view(number);

  //удалим пробелы с начала строки
  while (view.size() && isspace(view[0])) {
    view.remove_prefix(1);
  }

  //удалим пробелы с конца строки
  while (view.size() && isspace(view.back())) {
    view.remove_suffix(1);
  }

  //парсим знаки из начала строки и считаем итоговый
  is_negative = false;
  while (view.size() && (view[0] == '-' || view[0] == '+')) {
    if (view[0] == '-') {
      is_negative = !is_negative;
    }
    view.remove_prefix(1);
  }

  //разрежем строку по RANKS_LEN символов с конца
  //и таким образом парсим разряды
  ranks.reserve(view.size() / RANKS_LEN + 1);
  while (view.size()) {
    size_t rank_begin = RANKS_LEN < view.size() ? view.size() - RANKS_LEN : 0;
    auto rank_view = view.substr(rank_begin);

    size_t pos;
    int rank;
    try {
      rank = std::stoi(std::string(rank_view), &pos);
    } catch (const std::invalid_argument&) {
      throw std::invalid_argument(number + " is not a number.");
    }
    if (pos != rank_view.size() || rank_view[0] == '-' || rank_view[0] == '+' ||
        isspace(rank_view[0])) {
      throw std::invalid_argument(number + " is not a number.");
    }
    ranks.push_back(rank);
    view.remove_suffix(rank_view.size());
  }
}

BigInt& BigInt::operator=(const BigInt& copied) {
  ranks = copied.ranks;
  is_negative = copied.is_negative;
  return *this;
}

BigInt& BigInt::operator=(BigInt&& moved) {
  ranks = std::move(moved.ranks);
  is_negative = moved.is_negative;
  return *this;
}

std::ostream& operator<<(std::ostream& os, const BigInt& number) {
  if (number.ranks.size() == 0) {
    os << 0;
    return os;
  }

  if (number.is_negative) {
    os << '-';
  }

  os << std::setfill('0');
  for (size_t i = number.ranks.size(); i > 0; i--) {
    if (i != number.ranks.size()) {
      os << std::setw(BigInt::RANKS_LEN);
    }
    os << number.ranks[i - 1];
  }

  return os;
}

std::istream& operator>>(std::istream& is, BigInt& number) {
  std::string input_number;
  is >> input_number;
  number = BigInt(input_number);
  return is;
}

BigInt BigInt::operator-() {
  BigInt result(*this);
  result.is_negative = !is_negative;

  return result;
}

/*
BigInt operator+(const BigInt& lhs, const BigInt& rhs) {
  BigInt result;
  size_t max_size = std::max(lhs.ranks.size(), rhs.ranks.size());
  size_t min_size = std::min(lhs.ranks.size(), rhs.ranks.size());
  result.ranks.reserve(max_size + 1);
  Vector<int> overflow(result.ranks.size());

  for (size_t i = 0; i < min_size; i++) {

  }
}
*/
