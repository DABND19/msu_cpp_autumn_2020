#include <sstream>

#include "Serializers.hpp"
#include "test_runner.h"

using namespace std;

struct Data {
  uint64_t a;
  bool b;
  uint64_t c;

  template <class Serializer>
  Error serialize(Serializer& serializer) const {
    return serializer(a, b, c);
  }

  template <class Deserializer>
  Error deserialize(Deserializer& deserializer) {
    return deserializer(a, b, c);
  }
};

void SaveTest() {
  Data x = {1, true, 2};

  std::stringstream stream;

  Serializer serializer(stream);
  auto status = serializer.save(x);

  ASSERT_EQUAL(status, Error::NoError)
  ASSERT_EQUAL(stream.str(), "1 true 2 ")
}

void LoadTest() {
  Data x;

  std::stringstream stream("1 true 2");

  Deserializer serializer(stream);
  auto status = serializer.load(x);

  ASSERT_EQUAL(status, Error::NoError)
  ASSERT_EQUAL(x.a, 1u)
  ASSERT_EQUAL(x.b, true)
  ASSERT_EQUAL(x.c, 2u)
}

void IncorrectInputTest() {
  //отрицательные числа
  {
    Data x;

    std::stringstream stream("-1 true 2");

    Deserializer serializer(stream);
    ASSERT_EQUAL(serializer.load(x), Error::CorruptedArchive)
  }

  //не числа
  {
    Data x;

    std::stringstream stream("1a true 2");

    Deserializer serializer(stream);
    ASSERT_EQUAL(serializer.load(x), Error::CorruptedArchive)
  }

  //переполнение
  {
    Data x;

    std::stringstream stream("99999999999999999999999999999999999999 true 2");

    Deserializer serializer(stream);
    ASSERT_EQUAL(serializer.load(x), Error::CorruptedArchive)
  }
}

void YourTests() {
  Data x = {1, true, 2};

  std::stringstream stream;

  Serializer serializer(stream);
  serializer.save(x);

  Data y = {0, false, 0};

  Deserializer deserializer(stream);
  const Error err = deserializer.load(y);

  ASSERT_EQUAL(err, Error::NoError)

  ASSERT_EQUAL(x.a, y.a)
  ASSERT_EQUAL(x.b, y.b)
  ASSERT_EQUAL(x.c, y.c)
}

void RunTests() {
  TestRunner tr;
  RUN_TEST(tr, SaveTest);
  RUN_TEST(tr, LoadTest);
  RUN_TEST(tr, IncorrectInputTest);
  RUN_TEST(tr, YourTests);
}

int main() {
  RunTests();
  return 0;
}
