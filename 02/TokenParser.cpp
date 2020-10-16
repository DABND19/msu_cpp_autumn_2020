#include "TokenParser.h"
#include <exception>

void TokenParser::setStartTrigger(std::function<void(void)> startTrigger)
{
  start_trigger = startTrigger;
}

void TokenParser::setStringTrigger(std::function<void(const std::string &)> stringTrigger)
{
  string_trigger = stringTrigger;
}

void TokenParser::setNumberTrigger(std::function<void(int64_t)> numberTrigger)
{
  number_trigger = numberTrigger;
}

void TokenParser::setFinishTrigger(std::function<void(void)> finishTrigger)
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
        throw std::invalid_argument("");
      }

      number_trigger(number);
    }
    catch (...)
    {
      string_trigger(token);
    }
  }

  finish_trigger();
}

void TokenParser::runParser(const std::string& text)
{
  std::stringstream input(text);
  runParser(input);
}
