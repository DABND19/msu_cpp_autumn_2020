#pragma once

#include <iostream>
#include <functional>
#include <string>

class TokenParser
{
public:
  using Trigger = std::function<void(void)>;
  using StringTrigger = std::function<void(const std::string &)>;
  using NumberTrigger = std::function<void(int64_t)>;

  TokenParser() = default;

  void setStartTrigger(Trigger startTrigger);
  void setStringTrigger(StringTrigger stringTrigger);
  void setNumberTrigger(NumberTrigger numberTrigger);
  void setFinishTrigger(Trigger finishTrigger);

  void runParser(std::istream &input);
  void runParser(const std::string &text);

private:
  Trigger start_trigger = []() {};
  StringTrigger string_trigger = [](const std::string &) {};
  NumberTrigger number_trigger = [](int64_t) {};
  Trigger finish_trigger = []() {};
};
