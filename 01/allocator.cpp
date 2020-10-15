#include "allocator.h"

using namespace std;

Allocator::~Allocator()
{
  delete[] data;
}

void Allocator::makeAllocator(size_t maxSize)
{
  //  если вызываем метод второй раз 
  //  (т.е. в data уже что-то лежит)
  //  то делает delete []
  if (data != nullptr)
  {
    delete[] data;
  }

  data = new char[maxSize];
  capacity = maxSize;
  end = 0;
}

char *Allocator::alloc(size_t size)
{
  if (size + end > capacity)
  {
    return nullptr;
  }

  char *result = data + end;
  end += size;

  return result;
}

void Allocator::reset()
{
  end = 0;
}
