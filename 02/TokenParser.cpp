#include "TokenParser.h"
#include <sstream>
#include <exception>

void TokenParser::setStartTrigger(Trigger startTrigger)
{
  start_trigger = startTrigger;
}

void TokenParser::setStringTrigger(StringTrigger stringTrigger)
{
  string_trigger = stringTrigger;
}

void TokenParser::setNumberTrigger(NumberTrigger numberTrigger)
{
  number_trigger = numberTrigger;
}

void TokenParser::setFinishTrigger(Trigger finishTrigger)
{
  finish_trigger = finishTrigger;
}

void TokenParser::runParser(std::istream &input)
{
  start_trigger();

  std::string token;
  int64_t number;

  while (input >> token)
  {
    try
    {
      size_t pos;
      number = std::stoll(token, &pos);

      //  если в токене есть символы,
      //  которые не удалось конвертировать,
      //  то будем считать его строкой
      if (pos != token.size())
      {
        string_trigger(token);
      }
      else
      {
        number_trigger(number);
      }
    }
    catch (const std::logic_error &)
    {
      string_trigger(token);
    }
  }

  finish_trigger();
}

void TokenParser::runParser(const std::string &text)
{
  std::stringstream input(text);
  runParser(input);
}
