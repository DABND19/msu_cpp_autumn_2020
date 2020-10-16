#pragma once

#include <iostream>
#include <vector>
#include <functional>
#include <string>
#include <sstream>

class TokenParser
{
public:
  using Trigger = std::function<void(void)>;
  using StringTrigger = std::function<void(const std::string &)>;
  using NumberTrigger = std::function<void(int64_t)>;

  TokenParser() = default;

  void setStartTrigger(std::function<void(void)> startTrigger);
  void setStringTrigger(std::function<void(const std::string &)> stringTrigger);
  void setNumberTrigger(std::function<void(int64_t)> numberTrigger);
  void setFinishTrigger(std::function<void(void)> finishTrigger);

  void runParser(std::istream &input);
  void runParser(const std::string &text);

private:
  Trigger start_trigger = []() {};
  StringTrigger string_trigger = [](const std::string &) {};
  NumberTrigger number_trigger = [](int64_t) {};
  Trigger finish_trigger = []() {};
};
