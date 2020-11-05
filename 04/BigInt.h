#pragma once

#include <cmath>
#include <iostream>
#include <limits>
#include <string>

#include "Vector.h"

static const size_t RANK_LEN = std::numeric_limits<int>::digits10;
const int RADIX = static_cast<int>(std::pow(10, RANK_LEN));

class BigInt {
  Vector<int> ranks = Vector<int>(1, 0);
  bool is_negative = false;

 public:
  BigInt() = default;
  BigInt(int num);
  BigInt(Vector<int>&& ranks, bool is_negative);
  BigInt(const std::string& str_num);
  BigInt(const BigInt& copied);
  BigInt(BigInt&& moved);

  BigInt& operator=(const BigInt& copied);
  BigInt& operator=(BigInt&& moved);

  int sgn() const;
  BigInt operator-() const;
  int operator[](size_t index) const;
  size_t order() const { return ranks.size(); }

  BigInt& operator+=(const BigInt& rval);
  BigInt& operator-=(const BigInt& rval);
  BigInt& operator*=(const BigInt& rval);
};

bool operator<(const BigInt& lhs, const BigInt& rhs);
bool operator==(const BigInt& lhs, const BigInt& rhs);
bool operator!=(const BigInt& lhs, const BigInt& rhs);
bool operator<=(const BigInt& lhs, const BigInt& rhs);
bool operator>(const BigInt& lhs, const BigInt& rhs);
bool operator>=(const BigInt& lhs, const BigInt& rhs);

BigInt operator+(const BigInt& lhs, const BigInt& rhs);
BigInt operator-(const BigInt& lhs, const BigInt& rhs);
BigInt operator*(const BigInt& lhs, const BigInt& rhs);

std::ostream& operator<<(std::ostream& os, const BigInt& num);
