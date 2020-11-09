#include <iostream>
#include <limits>
#include <sstream>

#include "BigInt.h"
#include "test_runner.h"

using namespace std;

void TestCtors() {
  {
    BigInt zero;
    stringstream out;
    out << zero;
    ASSERT_EQUAL("0", out.str());
  }

  {
    const string num = "11111111111111111111111111111111111111";
    BigInt a(num);
    stringstream out;
    out << a;
    ASSERT_EQUAL(num, out.str());
  }

  {
    const string bad_num = "11111s11111111a11111111111d111111111f11111";
    bool is_catched = false;

    try {
      BigInt a(bad_num);
    } catch (std::invalid_argument&) {
      is_catched = true;
    }

    ASSERT(is_catched)
  }

  {
    const int num = 123456;
    BigInt a(num);

    stringstream out;
    out << a;

    ASSERT_EQUAL(out.str(), to_string(num))
  }

  {
    const string num = "11111111111111111111111111111111111111";
    BigInt copied(num);
    BigInt var(copied);

    stringstream out_var;
    out_var << var;

    stringstream out_copied;
    out_copied << copied;

    ASSERT_EQUAL(out_var.str(), out_copied.str());
  }

  {
    const string num = "11111111111111111111111111111111111111";
    BigInt moved(num);
    BigInt var(std::move(moved));

    stringstream out;
    out << var;

    ASSERT_EQUAL(moved.order(), 0u);
    ASSERT_EQUAL(out.str(), num);
  }
}

void TestAssignmentOps() {
  {
    const string num = "11111111111111111111111111111111111111";
    BigInt copied(num);
    BigInt var;

    var = copied;

    stringstream out_var;
    out_var << var;

    stringstream out_copied;
    out_copied << copied;

    ASSERT_EQUAL(out_var.str(), out_copied.str());
  }

  {
    const string num = "11111111111111111111111111111111111111";
    BigInt moved(num);
    BigInt var;

    var = std::move(moved);

    stringstream out;
    out << var;

    ASSERT_EQUAL(moved.order(), 0u);
    ASSERT_EQUAL(out.str(), num);
  }
}

void TestCompOps() {
  {
    BigInt a("1111111111111111111");
    BigInt b("2222222222222222222");

    ASSERT(a < b)
    ASSERT(a == a)
    ASSERT(a != b)
    ASSERT(a <= b)
    ASSERT(a >= 0)
  }
}

void TestArithmetic() {
  {
    BigInt a("1111111111111111111111111111111111111111111111111");

    ASSERT_EQUAL(-a, BigInt("-1111111111111111111111111111111111111111111111111"))
  }

  {
    BigInt a("1111111111111111111111111111111111111111111111111");
    BigInt b("1111111111111111111111111111111111111111111111111");

    ASSERT_EQUAL(a + b, BigInt("2222222222222222222222222222222222222222222222222"))
  }

  {
    BigInt a("1111111111111111111111111111111111111111111111111");

    ASSERT_EQUAL(2 * a, BigInt("2222222222222222222222222222222222222222222222222"))
  }

  {
    BigInt a("1111111111111111111111111111111111111111111111111");
    a += a;
    ASSERT_EQUAL(a, BigInt("2222222222222222222222222222222222222222222222222"))
  }

  {
    BigInt a("1111111111111111111111111111111111111111111111111");
    a -= a;
    ASSERT_EQUAL(a, BigInt(0))
  }

  {
    BigInt a("999999999999999999999999999999");
    a *= a;
    ASSERT_EQUAL(a, BigInt("999999999999999999999999999998000000000000000000000000000001"))
  }
}

void TestOutput() {
  const string num = "100000000000000000000000000000000000000000000000000000000000000000000000000000000";
    BigInt a(num);
    stringstream out;
    out << a;
    ASSERT_EQUAL(num, out.str());
}

void RunTests() {
  TestRunner tr;
  RUN_TEST(tr, TestCtors);
  RUN_TEST(tr, TestAssignmentOps);
  RUN_TEST(tr, TestCompOps);
  RUN_TEST(tr, TestArithmetic);
  RUN_TEST(tr, TestOutput);
}

int main() {
  RunTests();
  BigInt a(1);
  int k = 0;
  BigInt sum;
  do {
    sum += a;
    a *= 2;
    k++;
  } while(k <= 100'000);
  ASSERT_EQUAL(sum, a - 1)
  cout << sum << endl;
  return 0;
}