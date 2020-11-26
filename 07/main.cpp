#include <iostream>
#include <string>
#include <vector>

#include "Vector.hpp"

using namespace std;

int main() {
  Vector<int> a(50, 1);
  cout << a << endl;
  return 0;
}
