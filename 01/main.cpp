#include <iostream>
#include <cassert>
#include <string>
#include <sstream>
#include "allocator.h"

using namespace std;

void RunTests() 
{
  {
    Allocator allocator;

    assert(allocator.alloc(0) == nullptr);

    cerr << "empty allocator test is done!" << endl;
  }

  {
    Allocator allocator;
    allocator.makeAllocator(10);

    assert(allocator.alloc(150) == nullptr);

    cerr << "overflow allocator test is done!" << endl;
  }

  {
    Allocator allocator;
    allocator.makeAllocator(10);

    char *abcde = allocator.alloc(5);

    for (size_t i = 0; i < 5; ++i) {
      abcde[i] = 'a' + i;
    }

    assert(string(abcde, 5) == "abcde");

    cerr << "alloc test is done!" << endl;


    allocator.reset();

    abcde = allocator.alloc(5);

    assert(string(abcde, 5) == "abcde");

    cerr << "reset test is done!" << endl;
  }
}

int main()
{
  RunTests();
  return 0;
}
