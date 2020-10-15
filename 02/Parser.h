#pragma once

#include <string_view>
#include <vector>

std::vector<std::string_view> SplitIntoWords(std::string_view text);

class Parser
{
private:
  std::vector<std::string_view> tokens;
public:
  Parser(std::string_view input);

  template<typename TriggerD, typename TriggerW>
  void runTriggers(TriggerD DigitTrigger, TriggerW WordTrigger);
  ~Parser();
};
