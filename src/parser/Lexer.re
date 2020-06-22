open SyntaxError;

type lexer = {
  originalInput: string,
  currentInput: string,
  index: int,
};

type token =
  | INT(int)
  | STRING(string)
  | END
  | LPAREN
  | RPAREN;
// STRING
// SYMBOL

let newLexer = (input: string): lexer => {
  originalInput: input,
  currentInput: input,
  index: 0,
};

let skipCharacters = (lexer: lexer, stringToSkip: string): lexer => {
  let len = String.length(stringToSkip);
  let nextLexer: lexer = {
    originalInput: lexer.originalInput,
    currentInput:
      String.sub(
        lexer.currentInput,
        len,
        String.length(lexer.currentInput) - len,
      ),
    index: lexer.index + len,
  };
  nextLexer;
};

let whitespacePattern = [%re "/^\\s+/"];

let skipWhitspace = (lexer: lexer): lexer => {
  let result: option(array(Js.String.t)) =
    Js.String.match(whitespacePattern, lexer.currentInput);
  switch (result) {
  | Some(array) =>
    let stringToSkip = array[0];
    skipCharacters(lexer, stringToSkip);
  | _ => lexer
  };
};

let intPattern = [%re "/^(\\d+)/"];

let scanInt = (lexer: lexer): (token, lexer) => {
  let result: option(array(Js.String.t)) =
    Js.String.match(intPattern, lexer.currentInput);

  switch (result) {
  | Some(array) =>
    let digits = array[0];
    let token: token = INT(int_of_string(digits));
    let nextLexer: lexer = skipCharacters(lexer, digits);
    (token, nextLexer);
  | None => raise(SyntaxError("Not a number"))
  };
};

let stringPattern = [%re "/^\"([^\"]*)\"/"];

let scanString = (lexer: lexer): (token, lexer) => {
  let result: option(array(Js.String.t)) =
    Js.String.match(stringPattern, lexer.currentInput);

  switch (result) {
  | Some(array) =>
    let s = array[1];
    let token: token = STRING(s);
    let nextLexer: lexer = skipCharacters(lexer, array[0]);
    (token, nextLexer);
  | None => raise(SyntaxError("Missing closing \""))
  };
};

let isEnd = (lexer: lexer): bool => {
  String.length(lexer.currentInput) == 0;
};

let isDigit = (c: char) => c >= '0' && c <= '9';

let nextTokenFrom = (lexer: lexer): (token, lexer) => {
  let nextChar = lexer.currentInput.[0];

  switch (nextChar) {
  | '(' => (LPAREN, skipCharacters(lexer, "("))
  | ')' => (RPAREN, skipCharacters(lexer, ")"))
  | '"' => scanString(lexer)
  | _ when isDigit(nextChar) => scanInt(lexer)
  | _ => raise(SyntaxError("Bad syntax"))
  };
};

let nextToken = (lexer: lexer): (token, lexer) => {
  let lexer = skipWhitspace(lexer);
  if (isEnd(lexer)) {
    (END, lexer);
  } else {
    nextTokenFrom(lexer);
  };
};