#include <cmath>
#include <iostream>

#include "Exception.hpp"
#include "format.hpp"
#include "test_runner.h"

using namespace std;

void BasicTests() {
  // your test
  {
    auto text = format("{1} + {1} = {0}", 2, "one");
    ASSERT_EQUAL(text, "one + one = 2")
  }

  // without formatting
  {
    auto text = format("Hello, World!!!", "Goodbye, Cruel World!!!");
    ASSERT_EQUAL(text, "Hello, World!!!")
  }
}

void ExceptionsTests() {
  // too many args
  {
    bool is_catched = false;
    try {
      auto text = format("{1} + {1} = {3}", 2, "one");
    } catch (const InvalidArgs&) {
      is_catched = true;
    }
    ASSERT(is_catched)
  }

  // invalid scope sequnce 1
  {
    bool is_catched = false;
    try {
      auto text = format("{1} + {1} = {", 2, "one");
    } catch (const InvalidScopeSeq&) {
      is_catched = true;
    }
    ASSERT(is_catched)
  }

  // empty index
  {
    bool is_catched = false;
    try {
      auto text = format("{1} + {1} = {}", 2, "one");
    } catch (const InvalidIndex&) {
      is_catched = true;
    }
    ASSERT(is_catched)
  }

  // invalid index
  {
    bool is_catched = false;
    try {
      auto text = format("{1.5} + {1} = {0}", 2, "one");
    } catch (const InvalidIndex&) {
      is_catched = true;
    }
    ASSERT(is_catched)
  }

  // invalid scope sequnce 2
  {
    bool is_catched = false;
    try {
      auto text = format("{1} + 1} = {0}", 2, "one");
    } catch (const InvalidScopeSeq&) {
      is_catched = true;
    }
    ASSERT(is_catched)
  }
}

void RunTests() {
  TestRunner tr;
  RUN_TEST(tr, BasicTests);
  RUN_TEST(tr, ExceptionsTests);
}

int main() {
  RunTests();

  return 0;
}
