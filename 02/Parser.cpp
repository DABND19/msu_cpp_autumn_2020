#include "Parser.h"
#include <cctype>

using namespace std;


vector<string_view> split_into_words(string_view text)
{
  vector<string_view> result;

  while (true)
  {
    auto space = text.find(' ');
    result.push_back(text.substr(0, space));

    if (space == text.npos)
    {
      break;
    }
    else
    {
      text.remove_prefix(space + 1);
    }
  }

  return result;
}

TokenType get_token_type(string_view token)
{
  TokenType result = TokenType::Number;

  for (auto c : token)
  {
    if (!std::isdigit(c))
    {
      result = TokenType::Word;
      break;
    }
  }

  return result;
}

Parser::Parser(string_view input)
{
  for (auto token : split_into_words(input))
  {
    types.emplace_back(get_token_type(token));
  }
}

template <typename TriggerD, typename TriggerW>
void runTriggers(TriggerD DigitTrigger,
                 TriggerW WordTrigger)
{
}
