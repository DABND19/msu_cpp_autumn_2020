#pragma once

#include <iterator>
#include <memory>

template <typename T, class Allocator = std::allocator<T>>
class Vector;

template <typename T>
class RandomAccessIterator {
 public:
  using Self = RandomAccessIterator<T>;

 private:
  friend Vector<T>;
  T* current_;

 public:
  RandomAccessIterator(T* pos) : current_(pos) {}

  bool operator==(const Self& rhs) const { return current_ == rhs.current_; }
  bool operator!=(const Self& rhs) const { return current_ != rhs.current_; }
  bool operator<(const Self& rhs) const { return current_ < rhs.current_; }
  bool operator>(const Self& rhs) const { return current_ > rhs.current_; }
  bool operator<=(const Self& rhs) const { return current_ <= rhs.current_; }
  bool operator>=(const Self& rhs) const { return current_ >= rhs.current_; }

  Self& operator++() {
    current_++;
    return *this;
  }

  Self operator++(int) {
    auto result = *this;
    current_++;
    return result;
  }

  Self& operator--() {
    current_--;
    return *this;
  }

  Self operator--(int) {
    auto result = *this;
    current_--;
    return result;
  }

  Self operator+(ptrdiff_t shift) const { return {current_ + shift}; }
  Self operator-(ptrdiff_t shift) const { return {current_ - shift}; }

  Self& operator+=(ptrdiff_t shift) const { return *this = *this + shift; }

  Self& operator-=(ptrdiff_t shift) const { return *this = *this - shift; }

  T& operator*() { return *current_; }
  const T& operator*() const { return *current_; }
};

#pragma once

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

template <typename T, class Allocator>
class Vector {
 public:
  using value_type = T;
  using allocator_type = Allocator;
  using size_type = size_t;
  using reference = value_type&;
  using const_reference = const value_type&;

  using iterator = RandomAccessIterator<T>;
  using reverse_iterator = std::reverse_iterator<iterator>;

  Vector() = default;
  Vector(size_type size_);
  Vector(size_type size_, const_reference value);
  Vector(const Vector& copied);
  Vector(Vector&& moved);

  Vector& operator=(const Vector& copied);
  Vector& operator=(Vector&& moved);

  size_type size() const { return size_; }
  size_type capacity() const { return capacity_; }

  iterator begin() { return {data_}; }
  iterator end() { return {data_ + size_}; }
  reverse_iterator rbegin() { return std::make_reverse_iterator(end()); }
  reverse_iterator rend() { return std::make_reverse_iterator(begin()); }
  const_reference back() const;
  reference back();

  const_reference operator[](size_type index) const noexcept {
    return data_[index];
  }

  reference operator[](size_type index) noexcept { return data_[index]; }

  void reserve(size_type new_cap);
  void push_back(const_reference value);
  void push_back(value_type&& value);
  bool empty() const { return size_ == 0; }
  void pop_back();
  void clear();
  void resize(size_type new_size, const_reference& value);
  ~Vector();

 private:
  allocator_type alloc_ = Allocator();
  value_type* data_ = nullptr;
  size_type capacity_ = 0;
  size_type size_ = 0;
};

#include "Vector.ipp"
