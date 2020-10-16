#pragma once

#include <iostream>
#include <vector>
#include <functional>
#include <string>
#include <sstream>

class TokenParser
{
private:
  std::function<void(void)> start_trigger = []() {};
  std::function<void(const std::string &)> string_trigger = [](const std::string &) {};
  std::function<void(int64_t)> number_trigger = [](int64_t) {};
  std::function<void(void)> finish_trigger = []() {};

public:
  TokenParser() = default;

  void setStartTrigger(std::function<void(void)> startTrigger);
  void setStringTrigger(std::function<void(const std::string &)> stringTrigger);
  void setNumberTrigger(std::function<void(int64_t)> numberTrigger);
  void setFinishTrigger(std::function<void(void)> finishTrigger);

  void runParser(std::istream &input);
  void runParser(const std::string &text);
};
