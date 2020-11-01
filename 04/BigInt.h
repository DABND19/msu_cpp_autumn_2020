#pragma once

#include <cmath>
#include <iostream>
#include <limits>
#include <string>

#include "Vector.h"

class BigInt {
 public:
  BigInt() = default;
  BigInt(const std::string& number);
  BigInt(const BigInt& copied) = default;
  BigInt(BigInt&& moved) = default;
  BigInt& operator=(const BigInt& copied);
  BigInt& operator=(BigInt&& moved);
  ~BigInt() = default;
  friend std::ostream& operator<<(std::ostream& os, const BigInt& number);
  friend std::istream& operator>>(std::istream& is, BigInt& number);
  BigInt operator-();
  // friend BigInt operator+(const BigInt& lhs, const BigInt& rhs);

 private:
  std::pair<int, int> sumRanks(int lhs, int rhs);
  static const size_t RANKS_LEN = std::numeric_limits<int>::digits10 - 1;
  const size_t RADIX =
      static_cast<size_t>(std::pow(10, RANKS_LEN + 1));
  Vector<int> data;
  bool is_negative = false;
};
