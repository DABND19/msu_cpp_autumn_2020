#pragma once

#include <cstdlib>

class Allocator
{
private:
  char *data = nullptr;
  size_t capacity = 0;
  size_t end = 0;

public:
  ~Allocator();
  void makeAllocator(size_t maxSize);
  char *alloc(size_t size);
  void reset();
};
