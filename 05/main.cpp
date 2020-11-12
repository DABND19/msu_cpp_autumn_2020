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

void YourTest() {
  Data x = {1, true, 2};

  std::stringstream stream;

  Serializer serializer(stream);
  serializer.save(x);

  Data y = {0, false, 0};

  Deserializer deserializer(stream);
  const Error err = deserializer.load(y);

  ASSERT_EQUAL(err, Error::NoError);

  ASSERT_EQUAL(x.a, y.a);
  ASSERT_EQUAL(x.b, y.b);
  ASSERT_EQUAL(x.c, y.c);
}

void RunTests() {
  TestRunner tr;
  RUN_TEST(tr, YourTest);
}

int main() {
  RunTests();
  return 0;
}
