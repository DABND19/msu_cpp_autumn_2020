#include <string>

enum struct TokenType
{
  Word, Num
};

class Token
{
private:
  const TokenType type;
public:
  Token(/* args */);
  ~Token();
};

class Word : public Token
{
  private:
    std::string value;

  public:
    std::string getValue() const;
};

class Num : public Token
{
  private:
    uint64_t value;

  public:
    uint64_t getValue() const;
};
