open SyntaxError;
open Token;

type lexer = {
  originalInput: string,
  currentInput: string,
  index: int,
  token,
};

let newLexer = (input: string): lexer => {
  originalInput: input,
  currentInput: input,
  index: 0,
  token: END,
};

let advanceLexer =
    (lexer: lexer, stringToSkip: string, nextToken: token): lexer => {
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
    token: nextToken,
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
    advanceLexer(lexer, whitespace, lexer.token);
  | _ => lexer // No whitespace
  };
};

let intPattern = [%re "/^(\\d+)/"];

let scanInt = (lexer: lexer): lexer => {
  let result: option(array(Js.String.t)) =
    Js.String.match(intPattern, lexer.currentInput);

  switch (result) {
  | Some(array) =>
    let intString = array[0];
    let token: token = INT(int_of_string(intString));
    advanceLexer(lexer, intString, token);
  | None => raise(SyntaxError("Not a number"))
  };
};

let stringPattern = [%re "/^\"([^\"]*)\"/"];

let scanString = (lexer: lexer): lexer => {
  let result: option(array(Js.String.t)) =
    Js.String.match(stringPattern, lexer.currentInput);

  switch (result) {
  | Some(array) =>
    let quotedString = array[0];
    let unquotedString = array[1];
    let token: token = STRING(unquotedString);
    advanceLexer(lexer, quotedString, token);
  | None => raise(SyntaxError("Not a string"))
  };
};

let symbolPattern = [%re "/^[a-z_!+:$\\-]+/g"];

let scanSymbol = (lexer: lexer): lexer => {
  let result: option(array(Js.String.t)) =
    Js.String.match(symbolPattern, lexer.currentInput);

  switch (result) {
  | Some(array) =>
    let symbolName = array[0];
    let token: token = SYMBOL(symbolName);
    advanceLexer(lexer, symbolName, token);
  | None => raise(SyntaxError("Not a number"))
  };
};

let isEnd = (lexer: lexer): bool => String.length(lexer.currentInput) == 0;
let isInt = (s: string) => Js.String.match(intPattern, s) != None;
let isSymbol = (s: string) => Js.String.match(symbolPattern, s) != None;

let nextTokenFrom = (lexer: lexer): lexer => {
  let nextChar = lexer.currentInput.[0];
  switch (nextChar) {
  | '(' => advanceLexer(lexer, "(", LPAREN)
  | ')' => advanceLexer(lexer, ")", RPAREN)
  | '"' => scanString(lexer)
  | _ when isInt(lexer.currentInput) => scanInt(lexer)
  | _ when isSymbol(lexer.currentInput) => scanSymbol(lexer)
  | _ => raise(SyntaxError("Bad syntax"))
  };
};

let nextToken = (lexer: lexer): lexer => {
  let lexer = scanWhitspace(lexer);
  if (isEnd(lexer)) {
    {...lexer, token: END};
  } else {
    nextTokenFrom(lexer);
  };
};

let peekNextToken = (lexer: lexer): token => {
  let lexer = nextToken(lexer);
  lexer.token;
};