#include <chrono>
#include <iostream>
#include <string>
#include <vector>

#include "Vector.hpp"

using namespace std;

int main() {
  Vector<std::vector<int>> v;
  auto start = std::chrono::steady_clock::now();
  for (int i = 1; i < 10; ++i) {
    v.push_back(std::vector<int>(100000, i));
  }
  auto end = std::chrono::steady_clock::now();
  std::cout << "move semantic time: "
            << std::chrono::duration<double, std::milli>(end - start).count()
            << " ms" << std::endl;

  Vector<std::vector<int>> v1;
  start = std::chrono::steady_clock::now();
  for (int i = 1; i < 10; ++i) {
    std::vector<int> tmp(100000, i);
    v1.push_back(tmp);
  }
  end = std::chrono::steady_clock::now();
  std::cout << "copy time: "
            << std::chrono::duration<double, std::milli>(end - start).count()
            << " ms" << std::endl;
  return 0;
}