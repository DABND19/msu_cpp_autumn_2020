#pragma once

#include <algorithm>

template <typename T, class Allocator>
Vector<T, Allocator>::Vector(Vector<T, Allocator>::size_type size_)
    : data_(alloc_.allocate(size_)), capacity_(size_), size_(size_) {
  std::fill(begin(), end(), T());
}

template <typename T, class Allocator>
Vector<T, Allocator>::Vector(Vector<T, Allocator>::size_type size_,
                             const T& value)
    : data_(alloc_.allocate(size_)), capacity_(size_), size_(size_) {
  std::fill(begin(), end(), value);
}

template <typename T, class Allocator>
Vector<T, Allocator>::Vector(const Vector& copied)
    : alloc_(copied.alloc_),
      data_(alloc_.allocate(copied.capacity_)),
      capacity_(copied.capacity_),
      size_(copied.size_) {
  std::copy(copied.data_, copied.data_ + copied.size_, data_);
}

template <typename T, class Allocator>
Vector<T, Allocator>::Vector(Vector&& moved)
    : alloc_(moved.alloc_),
      data_(moved.data_),
      capacity_(moved.capacity_),
      size_(moved.size_) {
  moved.data_ = nullptr;
  moved.size_ = 0;
  moved.capacity_ = 0;
}

template <typename T, class Allocator>
Vector<T, Allocator>::~Vector() {
  clear();
}

template <typename T, class Allocator>
Vector<T, Allocator>& Vector<T, Allocator>::operator=(const Vector& copied) {
  if (data_ != copied.data_) {
    if (capacity_ == copied.capacity_) {
      std::copy(copied.data_, copied.data_ + copied.size_, data_);
    } else {
      Vector<T, Allocator> tmp(copied);
      std::swap(tmp.data_, data_);
      std::swap(tmp.capacity_, capacity_);
    }
    size_ = copied.size_;
  }

  return *this;
}

template <typename T, class Allocator>
Vector<T, Allocator>& Vector<T, Allocator>::operator=(Vector&& moved) {
  if (data_ != moved.data_) {
    Vector<T, Allocator> tmp(std::move(moved));
    std::swap(tmp.data_, data_);
    std::swap(tmp.size_, size_);
    std::swap(tmp.capacity_, capacity_);
  }

  return *this;
}

template <typename T, class Allocator>
void Vector<T, Allocator>::reserve(Vector<T, Allocator>::size_type new_cap) {
  if (new_cap > capacity_) {
    auto new_data = alloc_.allocate(new_cap);
    std::move(data_, data_ + capacity_, new_data);
    alloc_.deallocate(data_, capacity_);
    data_ = new_data;
    capacity_ = new_cap;
  }
}

template <typename T, class Allocator>
void Vector<T, Allocator>::push_back(const T& value) {
  if (size_ == capacity_) {
    auto new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
    reserve(new_capacity);
  }

  data_[size_++] = value;
}

template <typename T, class Allocator>
void Vector<T, Allocator>::push_back(T&& value) {
  if (size_ == capacity_) {
    auto new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
    reserve(new_capacity);
  }

  data_[size_++] = std::move(value);
}

template <typename T, class Allocator>
const T& Vector<T, Allocator>::back() const {
  if (empty()) {
    throw std::out_of_range("Vector is empty.");
  }

  return data_[size_ - 1];
}

template <typename T, class Allocator>
T& Vector<T, Allocator>::back() {
  if (empty()) {
    throw std::out_of_range("Vector is empty.");
  }

  return data_[size_ - 1];
}

template <typename T, class Allocator>
void Vector<T, Allocator>::pop_back() {
  if (!empty()) {
    size_--;
  }
}

template <typename T, class Allocator>
void Vector<T, Allocator>::clear() {
  alloc_.deallocate(data_, capacity_);
  capacity_ = size_ = 0;
}
