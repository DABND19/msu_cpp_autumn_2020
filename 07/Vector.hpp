#pragma once

#include <iostream>
#include <memory>
#include <initializer_list>

#include "VectorAllocator.hpp"
#include "VectorIterator.hpp"

template <typename T, class Allocator = VectorAllocator<T>>
class Vector {
 public:
  using iterator = VectorIterator<T>;
  using const_iterator = VectorIterator<T, const T&, const T*>;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

 private:
  Allocator allocator_ = Allocator();
  T* data_ = nullptr;
  size_t size_ = 0;
  size_t capacity_ = 0;

 public:
  Vector() = default;
  Vector(size_t size, const T& value = T());
  Vector(const Vector& copied);
  Vector(Vector&& moved);
  Vector(const std::initializer_list<T>& values);

  Vector& operator=(const Vector& copied);
  Vector& operator=(const Vector&& moved);

  size_t size() const { return size_; }
  size_t capacity() const { return capacity_; }
  bool empty() const { return size_ == 0; }

  T& back() { return data_[size_ - 1]; }
  const T& back() const { return data_[size_ - 1]; }

  iterator begin() { return {data_}; }
  iterator end() { return {data_ + size_}; }
  const_iterator begin() const { return {data_}; }
  const_iterator end() const { return {data_ + size_}; }

  reverse_iterator rbegin() { return std::make_reverse_iterator(end()); }
  reverse_iterator rend() { return std::make_reverse_iterator(begin()); }
  const_reverse_iterator rbegin() const {
    return std::make_reverse_iterator(end());
  }
  const_reverse_iterator rend() const {
    return std::make_reverse_iterator(begin());
  }

  T& operator[](size_t index) { return data_[index]; }
  const T& operator[](size_t index) const { return data_[index]; }

  void reserve(size_t capacity);
  void resize(size_t size, const T& value = T());
  void clear();

  ~Vector();

  void push_back(const T& value);
  void push_back(T&& value);
  void pop_back();

  template <typename... ArgsT>
  T& emplace_back(ArgsT&&... args);
};

template <typename T, class Allocator>
std::ostream& operator<<(std::ostream& os, const Vector<T, Allocator>& vector);

#include "Vector.ipp"
