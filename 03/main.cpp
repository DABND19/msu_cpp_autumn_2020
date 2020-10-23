#include <cassert>
#include <iostream>

#include "Matrix.h"
#include "test_runner.h"

using namespace std;

void TestCtors() {
  Matrix m(2, 2);

  auto [rows, columns] = m.getSize();

  ASSERT_EQUAL(rows, 2)
  ASSERT_EQUAL(columns, 2)

  m[0][0] = 1;
  m[0][1] = 2;
  m[1][0] = 3;
  m[1][1] = 4;

  Matrix a(m);

  ASSERT_EQUAL(a[0][0], 1)
  ASSERT_EQUAL(a[0][1], 2)
  ASSERT_EQUAL(a[1][0], 3)
  ASSERT_EQUAL(a[1][1], 4)
}

void TestIndexTakingOperator() {
  Matrix m(2, 2);

  m[0][0] = 1;
  m[0][1] = 2;
  m[1][0] = 3;
  m[1][1] = 4;

  ASSERT_EQUAL(m[0][0], 1)
  ASSERT_EQUAL(m[0][1], 2)
  ASSERT_EQUAL(m[1][0], 3)
  ASSERT_EQUAL(m[1][1], 4)

  m[0][0] *= 5;

  ASSERT(m[0][0] == 5)

  bool is_catched = false;

  try {
    m[3][1];
  } catch (const std::out_of_range&) {
    is_catched = true;
  }

  ASSERT(is_catched)

  is_catched = false;

  try {
    m[1][3];
  } catch (const std::out_of_range&) {
    is_catched = true;
  }

  ASSERT(is_catched)
}

void TestMultOperator() {
  Matrix m(2, 2);

  m[0][0] = 1;
  m[0][1] = 2;
  m[1][0] = 3;
  m[1][1] = 4;

  m *= 2;

  ASSERT_EQUAL(m[0][0], 2)
  ASSERT_EQUAL(m[0][1], 4)
  ASSERT_EQUAL(m[1][0], 6)
  ASSERT_EQUAL(m[1][1], 8)
}

void TestSumOperator() {
  {
    Matrix m(2, 2);
    Matrix a(1, 1);

    m[0][0] = 1;
    m[0][1] = 2;
    m[1][0] = 3;
    m[1][1] = 4;

    a[0][0] = 0;

    bool is_catched = false;

    try {
      a + m;
    } catch (const std::out_of_range&) {
      is_catched = true;
    }

    ASSERT(is_catched)
  }

  {
    Matrix m(2, 2);
    Matrix a(2, 2);

    m[0][0] = 1;
    m[0][1] = 2;
    m[1][0] = 3;
    m[1][1] = 4;

    a[0][0] = 4;
    a[0][1] = 3;
    a[1][0] = 2;
    a[1][1] = 1;

    Matrix sum(2, 2);
    sum = a + m;

    ASSERT_EQUAL(sum[0][0], 5)
    ASSERT_EQUAL(sum[0][1], 5)
    ASSERT_EQUAL(sum[1][0], 5)
    ASSERT_EQUAL(sum[1][1], 5)
  }
}

void TestEqualAndNotEqualOperators() {
  {
    Matrix m(2, 2);
    Matrix a(2, 2);

    m[0][0] = 1;
    m[0][1] = 2;
    m[1][0] = 3;
    m[1][1] = 4;

    a[0][0] = 4;
    a[0][1] = 3;
    a[1][0] = 2;
    a[1][1] = 1;

    ASSERT(a != m)
  }

  {
    Matrix m(2, 2);
    Matrix a(2, 2);

    m[0][0] = 1;
    m[0][1] = 2;
    m[1][0] = 3;
    m[1][1] = 4;

    a[0][0] = 1;
    a[0][1] = 2;
    a[1][0] = 3;
    a[1][1] = 4;

    ASSERT(a == m)
  }

  {
    Matrix m(2, 2);
    Matrix a(1, 1);

    m[0][0] = 1;
    m[0][1] = 2;
    m[1][0] = 3;
    m[1][1] = 4;

    a[0][0] = 0;

    bool is_catched = false;

    try {
      a == m;
    } catch (const std::out_of_range&) {
      is_catched = true;
    }

    ASSERT(is_catched)
  }
}

void TestAssignmentOperator() {
  Matrix m(2, 2);

  m[0][0] = 1;
  m[0][1] = 2;
  m[1][0] = 3;
  m[1][1] = 4;

  Matrix a(2, 2);
  a = m;

  ASSERT_EQUAL(a[0][0], 1)
  ASSERT_EQUAL(a[0][1], 2)
  ASSERT_EQUAL(a[1][0], 3)
  ASSERT_EQUAL(a[1][1], 4)
}

void RunTests() {
  TestRunner tr;
  RUN_TEST(tr, TestCtors);
  RUN_TEST(tr, TestIndexTakingOperator);
  RUN_TEST(tr, TestMultOperator);
  RUN_TEST(tr, TestSumOperator);
  RUN_TEST(tr, TestEqualAndNotEqualOperators);
  RUN_TEST(tr, TestAssignmentOperator);
}

int main() {
  RunTests();

  return 0;
}