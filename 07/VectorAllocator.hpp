#pragma once

#include <memory>

template <typename T>
class VectorAllocator {
 public:
  VectorAllocator() = default;
  ~VectorAllocator() = default;

  T* allocate(size_t n) { return new T[n]; }
  void deallocate(T* p, size_t n) { delete[] p; }
  void construct(T* p, const T& value) { *p = value; }
  void construct(T* p, T&& value) { *p = std::move(value); }
  void destroy(T* p) { p->~T(); }
};
