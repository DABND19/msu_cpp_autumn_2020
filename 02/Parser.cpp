#include "Parser.h"

using namespace std;

vector<string_view> SplitIntoWords(string_view text)
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

Parser::Parser(string_view input) {
  tokens = SplitIntoWords(input);
}

template<typename TriggerD, typename TriggerW>
void runTriggers(TriggerD DigitTrigger, 
                    TriggerW WordTrigger) 
{
  
}