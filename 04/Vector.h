#pragma once

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

template <typename T>
class Vector {
 public:
  Vector() = default;
  Vector(size_t size);
  Vector(size_t size, const T& value);
  Vector(const Vector& copied);
  Vector(Vector&& moved);
  Vector& operator=(const Vector& copied);
  Vector& operator=(Vector&& moved);
  size_t size() const { return size_; }
  size_t capacity() const { return capacity_; }
  T* begin() const { return data_; }
  T* end() const { return data_ + size_; }
  const T& operator[](size_t index) const;
  T& operator[](size_t index);
  void push_back(const T& value);
  void push_back(T&& value);
  ~Vector();

 private:
  T* data_ = nullptr;
  size_t capacity_ = 0;
  size_t size_ = 0;
};

template <typename T>
Vector<T>::Vector(size_t size)
    : data_(new T[size]), capacity_(size), size_(size) {}

template <typename T>
Vector<T>::Vector(size_t size, const T& value)
    : data_(new T[size]), capacity_(size), size_(size) {
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
void Vector<T>::push_back(const T& value) {
  if (size_ == capacity_) {
    if (capacity_ == 0) {
      capacity_ = 1;
    } else {
      capacity_ *= 2;
    }
    data_ = (T*)realloc(data_, capacity_ * sizeof(T));
  }

  data_[size_] = value;
  size_++;
}

template <typename T>
void Vector<T>::push_back(T&& value) {
  if (size_ == capacity_) {
    if (capacity_ == 0) {
      capacity_ = 1;
    } else {
      capacity_ *= 2;
    }
    data_ = (T*)realloc(data_, capacity_ * sizeof(T));
  }

  data_[size_] = std::move(value);
  size_++;
}
