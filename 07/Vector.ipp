#pragma once

#include "Vector.hpp"

template <typename T, class Allocator>
Vector<T, Allocator>::Vector(size_t size, const T& value)
    : data_(allocator_.allocate(size)), size_(size), capacity_(size) {
  for (size_t i = 0; i < size_; ++i) {
    allocator_.construct(data_ + i, value);
  }
}

template <typename T, class Allocator>
Vector<T, Allocator>::Vector(const Vector& copied)
    : data_(allocator_.allocate(copied.capacity_)),
      size_(copied.size_),
      capacity_(copied.capacity_) {
  for (size_t i = 0; i < size_; ++i) {
    allocator_.construct(data_ + i, copied[i]);
  }
}

template <typename T, class Allocator>
Vector<T, Allocator>::Vector(Vector&& moved)
    : data_(moved.data_), size_(moved.size_), capacity_(moved.capacity_) {
  moved.data_ = nullptr;
  moved.size_ = 0;
  moved.capacity_ = 0;
}

template <typename T, class Allocator>
Vector<T, Allocator>::Vector(const std::initializer_list<T>& values)
    : data_(allocator_.allocate(values.size())),
      size_(0),
      capacity_(values.size()) {
  for (const auto& value : values) {
    push_back(value);
  }
}

template <typename T, class Allocator>
Vector<T, Allocator>& Vector<T, Allocator>::operator=(const Vector& copied) {
  if (data_ != copied.data_) {
    Vector tmp(copied);
    std::swap(data_, tmp.data_);
    std::swap(size_, tmp.size_);
    std::swap(capacity_, tmp.capacity_);
  }

  return *this;
}

template <typename T, class Allocator>
Vector<T, Allocator>& Vector<T, Allocator>::operator=(const Vector&& moved) {
  if (data_ != moved.data_) {
    Vector tmp(std::move(moved));
    std::swap(data_, tmp.data_);
    std::swap(size_, tmp.size_);
    std::swap(capacity_, tmp.capacity_);
  }

  return *this;
}

template <typename T, class Allocator>
void Vector<T, Allocator>::reserve(size_t capacity) {
  if (capacity > capacity_) {
    auto tmp = allocator_.allocate(capacity);
    std::move(data_, data_ + size_, tmp);
    allocator_.deallocate(data_, capacity_);
    data_ = tmp;
    capacity_ = capacity;
  }
}

template <typename T, class Allocator>
void Vector<T, Allocator>::resize(size_t size, const T& value) {
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

template <typename T, class Allocator>
void Vector<T, Allocator>::clear() {
  for (size_t i = 0; i < size_; ++i) {
    allocator_.destroy(data_ + i);
  }

  allocator_.deallocate(data_, capacity_);
  data_ = nullptr;
  size_ = 0;
  capacity_ = 0;
}

template <typename T, class Allocator>
Vector<T, Allocator>::~Vector() {
  clear();
}

template <typename T, class Allocator>
void Vector<T, Allocator>::push_back(const T& value) {
  if (size_ == capacity_) {
    reserve(capacity_ ? capacity_ * 2 : 1);
  }

  allocator_.construct(data_ + size_++, value);
}

template <typename T, class Allocator>
void Vector<T, Allocator>::push_back(T&& value) {
  if (size_ == capacity_) {
    reserve(capacity_ ? capacity_ * 2 : 1);
  }

  allocator_.construct(data_ + size_++, std::move(value));
}

template <typename T, class Allocator>
void Vector<T, Allocator>::pop_back() {
  allocator_.destroy(data_ + --size_);
}

template <typename T, class Allocator>
template <typename... ArgsT>
T& Vector<T, Allocator>::emplace_back(ArgsT&&... args) {
  push_back({std::move(args)...});
  return back();
}

template <typename T, class Allocator>
std::ostream& operator<<(std::ostream& os, const Vector<T, Allocator>& vector) {
  for (const auto& item : vector) {
    os << item << ' ';
  }

  return os;
}
