#pragma once

#include <string_view>
#include <vector>

enum class TokenType
{
  Word,
  Number
};

std::vector<std::string_view> SplitIntoWords(std::string_view text);
bool is_number(std::string_view token);

class Parser
{
private:
  std::vector<TokenType> types;

public:
  Parser(std::string_view input);
  std::vector<TokenType> getTypes();
  template <typename TriggerD, typename TriggerW>
  void runTriggers(TriggerD DigitTrigger, TriggerW WordTrigger);
  ~Parser();
};
