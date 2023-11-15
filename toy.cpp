#include <iostream>

enum class Token {
  tok_eof = -1,
  tok_def = -2,
  tok_extern = -3,
  tok_identifier = -4,
  tok_number = -5,
};

static std::string IdentifierStr;
static double NumVal;

static int getTok() {
  static int LastChar = ' ';

  while (isspace(LastChar))
    LastChar = getchar();

  if (isalpha(LastChar)) {
    IdentifierStr = LastChar;
    while (isalnum((LastChar = getchar())))
      IdentifierStr += LastChar;

    if (IdentifierStr == "def")
      return static_cast<int>(Token::tok_def);
    if (IdentifierStr == "extern")
      return static_cast<int>(Token::tok_extern);
    return static_cast<int>(Token::tok_identifier);
  }
}

int main() {
  return 0;
}
