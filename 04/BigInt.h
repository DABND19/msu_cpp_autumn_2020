#pragma once

#include <iostream>
#include <string>

class BigInt {
 private:
  int16_t* data = nullptr;
  size_t capacity = 0;
  size_t size = 0;
  bool is_negative = false;

  //  inline int16_t* begin() const { return data; }
  //  inline int16_t* end() const { return data + size; }

 public:
  BigInt() = default;
  BigInt(const std::string& number);
  BigInt(const BigInt& copied);
  BigInt(BigInt&& moved);
  BigInt& operator=(const BigInt& copied);
  BigInt& operator=(BigInt&& moved);
  template <typename Integer>
  BigInt(Integer number);
  ~BigInt();

  friend std::ostream& operator<<(std::ostream& os, const BigInt& number);
};
