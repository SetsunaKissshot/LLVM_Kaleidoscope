#include <cctype>
#include <iostream>

// The lexer returns tokens [0-255] if it is an unknown character, otherwise one
// of these for known things.
enum class Token {
  tok_eof = -1,

  // commands
  tok_def = -2,
  tok_extern = -3,

  // primary
  tok_identifier = -4,
  tok_number = -5,
};

static std::string IdentifierStr; // Filled in if tok_identifier
static double NumVal;             // Filled in if tok_number

static int getTok() {
  static int LastChar = ' ';

  while (std::isspace(LastChar))
    LastChar = getchar();

  if (std::isalpha(LastChar)) {
    IdentifierStr = LastChar;
    while (std::isalnum((LastChar = getchar())))
      IdentifierStr += LastChar;

    if (IdentifierStr == "def")
      return static_cast<int>(Token::tok_def);
    if (IdentifierStr == "extern")
      return static_cast<int>(Token::tok_extern);
    return static_cast<int>(Token::tok_identifier);
  }

  if (std::isdigit(LastChar) || LastChar == '.') {
    std::string NumStr;
    do {
      NumStr += LastChar;
      LastChar = getchar();
    } while (std::isdigit(LastChar) || LastChar == '.');

    NumVal = strtod(NumStr.c_str(), 0);
    return static_cast<int>(Token::tok_number);
  }

  if (LastChar == '#') {
    do
      LastChar = getchar();
    while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');

    if (LastChar != EOF)
      return getTok();
  }

  if (LastChar == EOF)
    return static_cast<int>(Token::tok_eof);

  int ThisChar = LastChar;
  LastChar = getchar();
  return ThisChar;
}

int main() {
  return 0;
}
