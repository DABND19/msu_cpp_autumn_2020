#include <iostream>
#include <sstream>
#include <string>
#include <functional>
#include <cassert>
#include "TokenParser.h"

void TestWithoutTriggers()
{
  TokenParser p;

  p.runParser("Hello, World!!!");

  std::cerr << "Test without triggers done!" << std::endl;
}

void TestEmptyString()
{
  TokenParser p;
  std::stringstream output;

  p.setStartTrigger([&output]() {
    output << "s ";
  });

  p.setNumberTrigger([&output](int64_t number) {
    output << "n ";
  });

  p.setStringTrigger([&output](const std::string& word) {
    output << "w ";
  });

  p.setFinishTrigger([&output]() {
    output << "f";
  });

  p.runParser("");

  assert(output.str() == "s f");
  std::cerr << "Test empty string is done!" << std::endl;
}

void TestTokenTypesAndChangeTriggers()
{
  TokenParser p;
  std::stringstream output;
  const std::string text = "123 abcd ab12 12ab 12345bvd123 987a987 aaaa 123456789";

  p.setStartTrigger([&output]() {
    output << "s ";
  });

  p.setNumberTrigger([&output](int64_t number) {
    output << "n ";
  });

  p.setStringTrigger([&output](const std::string& word) {
    output << "w ";
  });

  p.setFinishTrigger([&output]() {
    output << "f";
  });

  p.runParser(text);

  assert(output.str() == "s n w w w w w w n f");
  std::cerr << "Test token types is done!" << std::endl;

  p.setNumberTrigger([&output](int64_t number) {
    output << "1 ";
  });

  p.setStringTrigger([&output](const std::string& word) {
    output << "0 ";
  });

  output = std::stringstream("");

  p.runParser(text);

  assert(output.str() == "s 1 0 0 0 0 0 0 1 f");
  std::cerr << "Test change triggers is done!" << std::endl;
}

void RunTests()
{
  TestWithoutTriggers();
  TestEmptyString();
  TestTokenTypesAndChangeTriggers();
}

int main()
{
  RunTests();
  return 0;
}