#include "BigInt.h"

#include <iomanip>
#include <string_view>

#include "Parse.h"

BigInt::BigInt(int num) {
  if (num != 0) {
    ranks = Vector<int>();
    is_negative = num < 0;
    num = abs(num);
    while (num) {
      ranks.push_back(num % RADIX);
      num /= RADIX;
    }
  }
}

BigInt::BigInt(Vector<int>&& ranks, bool is_negative)
    : ranks(std::move(ranks)), is_negative(is_negative) {
  if (this->ranks.empty()) {
    this->ranks = Vector<int>(1, 0);
  }

  while (this->ranks.size() > 1 && !this->ranks.back()) {
    this->ranks.pop_back();
  }
}

BigInt::BigInt(const std::string& str_num) {
  std::string_view view(str_num);

  removeSpacesAround(view);
  is_negative = parseAndRemoveSign(view);
  ranks = parseRanks(view, RANK_LEN);

  if (ranks.empty()) {
    ranks = Vector<int>(1, 0);
    is_negative = false;
  }
}

BigInt::BigInt(const BigInt& copied)
    : ranks(copied.ranks), is_negative(copied.is_negative) {}

BigInt::BigInt(BigInt&& moved)
    : ranks(std::move(moved.ranks)), is_negative(moved.is_negative) {}

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

int BigInt::sgn() const {
  if (ranks.back() == 0 || ranks.empty()) {
    return 0;
  }

  if (is_negative) {
    return -1;
  }

  return 1;
}

BigInt BigInt::operator-() const {
  BigInt result;
  result.ranks = ranks;
  result.is_negative = !is_negative;
  return result;
}

int BigInt::operator[](size_t index) const {
  if (index >= ranks.size()) {
    return 0;
  }

  return sgn() * ranks[index];
}

bool operator<(const BigInt& lhs, const BigInt& rhs) {
  if (lhs.sgn() == rhs.sgn()) {
    for (size_t i = std::max(lhs.order(), rhs.order()); i > 0; i--) {
      if (lhs[i - 1] != rhs[i - 1]) {
        return lhs[i - 1] < rhs[i - 1];
      }
    }

    return true;
  }

  return lhs.sgn() < rhs.sgn();
}

bool operator==(const BigInt& lhs, const BigInt& rhs) {
  if (lhs.sgn() != rhs.sgn()) {
    return false;
  }

  for (size_t i = std::max(lhs.order(), rhs.order()); i > 0; i--) {
    if (lhs[i - 1] != rhs[i - 1]) {
      return false;
    }
  }

  return true;
}

bool operator!=(const BigInt& lhs, const BigInt& rhs) { return !(lhs == rhs); }

bool operator<=(const BigInt& lhs, const BigInt& rhs) {
  return lhs < rhs || lhs == rhs;
}

bool operator>(const BigInt& lhs, const BigInt& rhs) { return !(lhs <= rhs); }

bool operator>=(const BigInt& lhs, const BigInt& rhs) { return !(lhs < rhs); }

Vector<int> sumRanks(const BigInt& lhs, const BigInt& rhs) {
  Vector<int> ranks_sum;
  ranks_sum.reserve(std::max(lhs.order(), rhs.order()) + 1);
  int overflow = 0;
  for (size_t i = 0; i < std::max(lhs.order(), rhs.order()); i++) {
    int sum = abs(overflow + lhs[i] + rhs[i]);
    overflow = sum / RADIX;
    sum %= RADIX;
    ranks_sum.push_back(sum);
  }

  return ranks_sum;
}

Vector<int> diffRanks(const BigInt& long_num, const BigInt& short_num) {
  Vector<int> ranks_diff;
  ranks_diff.reserve(long_num.order());
  int overflow = 0;
  for (size_t i = 0; i < long_num.order(); i++) {
    int diff = abs(long_num[i]) - abs(short_num[i]) + overflow;
    overflow = diff < 0 ? -1 : 0;
    if (diff < 0) {
      diff += RADIX;
    }
    ranks_diff.push_back(diff);
  }

  return ranks_diff;
}

BigInt operator+(const BigInt& lhs, const BigInt& rhs) {
  Vector<int> ranks_sum;
  int sgn_sum;

  if (lhs.sgn() == rhs.sgn()) {
    sgn_sum = lhs.sgn();
    ranks_sum = sumRanks(lhs, rhs);
  } else {
    bool lhs_abs_greater = true;
    if (lhs.order() == rhs.order()) {
      for (size_t i = lhs.order(); i > 0; i--) {
        if (abs(lhs[i - 1]) != abs(rhs[i - 1])) {
          lhs_abs_greater = abs(lhs[i - 1]) > abs(rhs[i - 1]);
          break;
        }
      }
    } else {
      lhs_abs_greater = lhs.order() > rhs.order();
    }

    if (lhs_abs_greater) {
      ranks_sum = diffRanks(lhs, rhs);
      sgn_sum = lhs.sgn();
    } else {
      ranks_sum = diffRanks(rhs, lhs);
      sgn_sum = rhs.sgn();
    }
  }

  return BigInt(std::move(ranks_sum), sgn_sum == -1);
}

BigInt operator-(const BigInt& lhs, const BigInt& rhs) { return lhs + (-rhs); }

BigInt operator*(const BigInt& lhs, const BigInt& rhs) {
  int sgn_prod = lhs.sgn() * rhs.sgn();
  if (sgn_prod == 0) {
    return 0;
  }

  Vector<int> rank_prod(lhs.order() + rhs.order() + 1);

  int64_t overflow = 0;
  for (size_t i = 0; i < lhs.order(); i++) {
    for (size_t j = 0; j < rhs.order(); j++) {
      int64_t prod = rank_prod[i + j] +
                     static_cast<int64_t>(abs(lhs[i])) *
                         static_cast<int64_t>(abs(rhs[j])) +
                     overflow;
      rank_prod[i + j] = prod % static_cast<int64_t>(RADIX);
      overflow = prod / static_cast<int64_t>(RADIX);
    }
  }
  rank_prod[lhs.order() + rhs.order()] = overflow;
  return BigInt(std::move(rank_prod), sgn_prod == -1);
}

BigInt& BigInt::operator+=(const BigInt& rval) { return *this = *this + rval; }

BigInt& BigInt::operator-=(const BigInt& rval) { return *this = *this - rval; }

BigInt& BigInt::operator*=(const BigInt& rval) { return *this = *this * rval; }

std::ostream& operator<<(std::ostream& os, const BigInt& num) {
  if (num.sgn() == -1) {
    os << '-';
  }

  os << std::setfill('0');
  for (size_t i = num.order(); i > 0; i--) {
    if (i != num.order()) {
      os << std::setw(RANK_LEN);
    }
    os << abs(num[i - 1]);
  }

  return os;
}
