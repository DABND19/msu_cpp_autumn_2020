#pragma once

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

template <typename T>
class Vector {
 public:
  Vector() = default;
  Vector(size_t size_);
  Vector(size_t size_, const T& value);
  Vector(const Vector& copied);
  Vector(Vector&& moved);
  Vector& operator=(const Vector& copied);
  Vector& operator=(Vector&& moved);
  size_t size() const { return size_; }
  size_t capacity() const { return capacity_; }
  T* begin() { return data_; }
  T* end() { return data_ + size_; }
  const T* begin() const { return data_; }
  const T* end() const { return data_ + size_; }
  const T& back() const;
  T& back();
  const T& operator[](size_t index) const;
  T& operator[](size_t index);
  void reserve(size_t new_cap);
  void push_back(const T& value);
  void push_back(T&& value);
  ~Vector();

 private:
  T* data_ = nullptr;
  size_t capacity_ = 0;
  size_t size_ = 0;
};

template <typename T>
Vector<T>::Vector(size_t size_)
    : data_(new T[size_]), capacity_(size_), size_(size_) {}

template <typename T>
Vector<T>::Vector(size_t size_, const T& value)
    : data_(new T[size_]), capacity_(size_), size_(size_) {
  std::fill(begin(), end(), value);
}

template <typename T>
Vector<T>::Vector(const Vector& copied)
    : data_(new T[copied.capacity_]),
      capacity_(copied.capacity_),
      size_(copied.size_) {
  std::copy(copied.begin(), copied.end(), begin());
}

template <typename T>
Vector<T>::Vector(Vector&& moved)
    : data_(moved.data_), capacity_(moved.capacity_), size_(moved.size_) {
  moved.data_ = nullptr;
  moved.size_ = 0;
  moved.capacity_ = 0;
}

template <typename T>
Vector<T>::~Vector() {
  delete[] data_;
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& copied) {
  if (data_ != copied.data_) {
    if (capacity_ == copied.capacity_) {
      std::copy(copied.begin(), copied.end(), begin());
    } else {
      Vector<T> tmp(copied);
      std::swap(tmp.data_, data_);
      std::swap(tmp.capacity_, capacity_);
    }
    size_ = copied.size_;
  }

  return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector&& moved) {
  if (data_ != moved.data_) {
    Vector<T> tmp(std::move(moved));
    std::swap(tmp.data_, data_);
    std::swap(tmp.size_, size_);
    std::swap(tmp.capacity_, capacity_);
  }

  return *this;
}

template <typename T>
const T& Vector<T>::operator[](size_t index) const {
  if (index >= size_) {
    throw std::out_of_range("index out of range.");
  }

  return data_[index];
}

template <typename T>
T& Vector<T>::operator[](size_t index) {
  if (index >= size_) {
    throw std::out_of_range("index out of range.");
  }

  return data_[index];
}

template <typename T>
void Vector<T>::reserve(size_t new_cap) {
  if (new_cap > capacity_) {
    auto new_data = new T[new_cap];
    std::move(data_, data_ + capacity_, new_data);
    delete[] data_;
    data_ = new_data;
    capacity_ = new_cap;
  }
}

template <typename T>
void Vector<T>::push_back(const T& value) {
  if (size_ == capacity_) {
    auto new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
    reserve(new_capacity);
  }

  data_[size_] = value;
  size_++;
}

template <typename T>
void Vector<T>::push_back(T&& value) {
  if (size_ == capacity_) {
    auto new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
    reserve(new_capacity);
  }

  data_[size_] = value;
  size_++;
}

template <typename T>
const T& Vector<T>::back() const {
  if (size == 0) {
    throw std::out_of_range("Vector is empty.");
  }

  return data_[size_ - 1];
}

template <typename T>
T& Vector<T>::back() {
  if (size == 0) {
    throw std::out_of_range("Vector is empty.");
  }

  return data_[size_ - 1];
}
