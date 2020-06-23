open SyntaxError;
open Token;

type lexer = {
  originalInput: string,
  currentInput: string,
  index: int,
};

let newLexer = (input: string): lexer => {
  originalInput: input,
  currentInput: input,
  index: 0,
};

let advanceLexer = (lexer: lexer, stringToSkip: string): lexer => {
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

let scanWhitspace = (lexer: lexer): lexer => {
  let result: option(array(Js.String.t)) =
    Js.String.match(whitespacePattern, lexer.currentInput);
  switch (result) {
  | Some(array) =>
    let whitespace = array[0];
    advanceLexer(lexer, whitespace);
  | _ => lexer // No whitespace
  };
};

let intPattern = [%re "/^(\\d+)/"];

let scanInt = (lexer: lexer): (token, lexer) => {
  let result: option(array(Js.String.t)) =
    Js.String.match(intPattern, lexer.currentInput);

  switch (result) {
  | Some(array) =>
    let intString = array[0];
    let token: token = INT(int_of_string(intString));
    let nextLexer: lexer = advanceLexer(lexer, intString);
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
    let quotedString = array[0];
    let unquotedString = array[1];
    let token: token = STRING(unquotedString);
    let nextLexer: lexer = advanceLexer(lexer, quotedString);
    (token, nextLexer);
  | None => raise(SyntaxError("Not a string"))
  };
};

let symbolPattern = [%re "/^[a-z_!+:$\\-]+/g"];

let scanSymbol = (lexer: lexer): (token, lexer) => {
  let result: option(array(Js.String.t)) =
    Js.String.match(symbolPattern, lexer.currentInput);

  switch (result) {
  | Some(array) =>
    let symbolName = array[0];
    let token: token = SYMBOL(symbolName);
    let nextLexer: lexer = advanceLexer(lexer, symbolName);
    (token, nextLexer);
  | None => raise(SyntaxError("Not a number"))
  };
};

let isEnd = (lexer: lexer): bool => String.length(lexer.currentInput) == 0;
let isInt = (s: string) => Js.String.match(intPattern, s) != None;
let isSymbol = (s: string) => Js.String.match(symbolPattern, s) != None;

let nextTokenFrom = (lexer: lexer): (token, lexer) => {
  let nextChar = lexer.currentInput.[0];
  switch (nextChar) {
  | '(' => (LPAREN, advanceLexer(lexer, "("))
  | ')' => (RPAREN, advanceLexer(lexer, ")"))
  | '"' => scanString(lexer)
  | _ when isInt(lexer.currentInput) => scanInt(lexer)
  | _ when isSymbol(lexer.currentInput) => scanSymbol(lexer)
  | _ => raise(SyntaxError("Bad syntax"))
  };
};

let nextToken = (lexer: lexer): (token, lexer) => {
  let lexer = scanWhitspace(lexer);
  if (isEnd(lexer)) {
    (END, lexer);
  } else {
    nextTokenFrom(lexer);
  };
};

let peekNextToken = (lexer: lexer): token => {
  let (token, _lexer) = nextToken(lexer);
  token;
};