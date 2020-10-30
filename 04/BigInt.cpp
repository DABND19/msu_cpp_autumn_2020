#include "BigInt.h"

#include <sstream>
#include <stdexcept>

BigInt::BigInt(const std::string& number) {
  size = 0;
  capacity = number.size();
  data = new int16_t[capacity];

  is_negative = false;

  bool expect_digits = true;

  for (auto it = number.rbegin(); it != number.rend(); it++) {
    auto symbol = *it;

    if (isdigit(symbol) && expect_digits) {
      data[size] = symbol - '0';
      size++;
    } else if (symbol == '-') {
      is_negative = !is_negative;
      expect_digits = false;
    } else {
      std::stringstream error_mesage;
      error_mesage << number << " is not number.";
      throw std::invalid_argument(error_mesage.str());
    }
  }
}

template<typename Integer>
BigInt::BigInt(Integer number) {
  std::stringstream string_num;
  string_num << number;
  *this = BigInt(string_num.str());
}

BigInt::~BigInt() {
  delete[] data;
}

std::ostream& operator<<(std::ostream& os, const BigInt& number) {
  if (number.is_negative) {
    os << '-';
  }

  for (int i = number.size - 1; i >= 0; i--) {
    os << number.data[i];
  }

  return os;
}
