#include <iostream>
#include "Vector.h"

using namespace std;

int main() {
  Vector<double> b;
  b.push_back(1);
  cout << b[0] << endl;
  cout << b.capacity() << endl;
  b.push_back(1);
  cout << b.capacity() << endl;
  b.push_back(1);
  cout << b.capacity() << endl;
  b.push_back(1);
  cout << b.capacity() << endl;
  return 0;
}