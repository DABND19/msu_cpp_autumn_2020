#pragma once

#include <iostream>
#include <memory>

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

  Vector(size_t size, const T& value = T())
      : data_(allocator_.allocate(size)), size_(size), capacity_(size) {
    for (size_t i = 0; i < size_; ++i) {
      allocator_.construct(data_ + i, value);
    }
  }

  Vector(const Vector& copied)
      : data_(allocator_.allocate(copied.capacity_)),
        size_(copied.size_),
        capacity_(copied.capacity_) {
    for (size_t i = 0; i < size_; ++i) {
      allocator_.construct(data_ + i, copied[i]);
    }
  }

  Vector(Vector&& moved)
      : data_(moved.data_), size_(moved.size_), capacity_(moved.capacity_) {
    moved.data_ = nullptr;
    moved.size_ = 0;
    moved.capacity_ = 0;
  }

  Vector& operator=(const Vector& copied) {
    if (data_ != copied.data_) {
      Vector tmp(copied);
      std::swap(data_, tmp.data_);
      std::swap(size_, tmp.size_);
      std::swap(capacity_, tmp.capacity_);
    }

    return *this;
  }

  Vector& operator=(const Vector&& moved) {
    if (data_ != moved.data_) {
      Vector tmp(std::move(moved));
      std::swap(data_, tmp.data_);
      std::swap(size_, tmp.size_);
      std::swap(capacity_, tmp.capacity_);
    }

    return *this;
  }

  size_t size() const { return size_; }
  size_t capacity() const { return capacity_; }
  bool empty() const { return size_ == 0; }

  T& back() { return data_ + size_ - 1; }
  const T& back() const { return data_ + size_ - 1; }

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

  void reserve(size_t capacity) {
    if (capacity > capacity_) {
      auto tmp = allocator_.allocate(capacity);
      std::move(data_, data_ + size_, tmp);
      allocator_.deallocate(data_, capacity_);
      data_ = tmp;
      capacity_ = capacity;
    }
  }

  void resize(size_t size, const T& value = T()) {
    if (size > capacity_) {
      reserve(size);
    }

    if (size > size_) {
      for (size_t i = size_; i < size; ++i) {
        allocator_.construct(data_ + i, value);
      }
    } else {
      for (size_t i = size; i < size_; ++i) {
        allocator_.destroy(data_ + i);
      }
    }

    size_ = size;
  }

  void clear() {
    for (size_t i = 0; i < size_; ++i) {
      allocator_.destroy(data_ + i);
    }

    allocator_.deallocate(data_, capacity_);
    data_ = nullptr;
    size_ = 0;
    capacity_ = 0;
  }

  ~Vector() { clear(); }

  void push_back(const T& value) {
    if (size_ == capacity_) {
      reserve(capacity_ ? capacity_ * 2 : 1);
    }

    allocator_.construct(data_ + size_++, value);
  }

  void push_back(T&& value) {
    if (size_ == capacity_) {
      reserve(capacity_ ? capacity_ * 2 : 1);
    }

    allocator_.construct(data_ + size_++, std::move(value));
  }

  void pop_back() { allocator_.destroy(data_ + --size_); }
};

template <typename T, class Allocator>
std::ostream& operator<<(std::ostream& os, const Vector<T, Allocator>& vector) {
  for (const auto& item : vector) {
    os << item << ' ';
  }

  return os;
}
