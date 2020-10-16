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

void TestChangeInputs()
{
  const std::string input1 = "a b c d e f 1 2 3 4 5 6";
  const std::string input2 = "g h i j k l 3 4 5 6 7";
  std::stringstream output;

  TokenParser p;

  p.setStringTrigger([&output](const std::string& word) {
    output << word << " ";
  });

  p.setNumberTrigger([&output](int64_t number) {
    output << number << " ";
  });

  p.runParser(input1);

  assert(output.str() == (input1 + " "));

  output = std::stringstream("");

  p.runParser(input2);

  assert(output.str() == (input2 + " "));

  std::cerr << "Test change inputs is done!" << std::endl;
}

void RunTests()
{
  TestWithoutTriggers();
  TestEmptyString();
  TestTokenTypesAndChangeTriggers();
  TestChangeInputs();
}

int main()
{
  RunTests();
  return 0;
}