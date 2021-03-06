#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>

#include "Vector.hpp"
#include "test_runner.h"

using namespace std;

void TestCtors() {
  {
    Vector<int> v;
    ASSERT_EQUAL(v.size(), 0u)
    ASSERT_EQUAL(v.capacity(), 0u);
  }

  {
    Vector<int> v(5, 5);
    stringstream ss;
    ss << v;
    ASSERT_EQUAL(ss.str(), "5 5 5 5 5 ")
    ASSERT_EQUAL(v.size(), 5u)
    ASSERT_EQUAL(v.capacity(), 5u)
  }

  {
    Vector<string> v_copied(5, "Hello");
    Vector<string> v_target(v_copied);

    stringstream ss1, ss2;

    ss1 << v_copied;
    ss2 << v_target;

    ASSERT_EQUAL(ss1.str(), ss2.str())
  }

  {
    Vector<string> v_moved(5, "Hello");
    Vector<string> v_target(std::move(v_moved));

    stringstream ss1, ss2;

    ss1 << v_moved;
    ss2 << v_target;

    ASSERT_EQUAL(v_moved.size(), 0u)
    ASSERT_EQUAL(v_moved.capacity(), 0u)
    ASSERT_EQUAL(ss1.str(), "")

    ASSERT_EQUAL(v_target.size(), 5u)
    ASSERT_EQUAL(v_target.capacity(), 5u)
  }
}

void TestMethods() {
  {
    Vector<int> v;
    ASSERT(v.empty())
  }

  {
    Vector<int> v;
    v.push_back(1);

    ASSERT_EQUAL(v[0], 1)
  }

  {
    Vector<int> v(1, 1);
    v.pop_back();

    ASSERT(v.empty())
  }

  {
    Vector<int> v;
    v.reserve(5);
    ASSERT_EQUAL(v.capacity(), 5u)
    ASSERT_EQUAL(v.size(), 0u)
  }

  {
    Vector<int> v(5, 5);
    v.resize(3);
    ASSERT_EQUAL(v.size(), 3u)
  }

  {
    Vector<string, allocator<string>> v;
    string str = "Hello";
    v.push_back(std::move(str));

    ASSERT(str.empty())
  }

  {
    Vector<pair<int, int>> v;
    auto res = v.emplace_back(1, 1);

    ASSERT(res == make_pair(1, 1))
  }

  {
    Vector<string> v(1'000'000, "Hello");
    v.clear();
    ASSERT(v.empty())
  }

  {
    Vector<int> v = {1, 2, 3, 4, 5};
    stringstream reverse;
    for (auto it = v.rbegin(); it != v.rend(); it++) {
      reverse << *it << ' ';
    }

    ASSERT_EQUAL("5 4 3 2 1 ", reverse.str())
  }
}

void RunTests() {
  TestRunner tr;
  RUN_TEST(tr, TestCtors);
  RUN_TEST(tr, TestMethods);
}

int main() {
  RunTests();
  return 0;
}
