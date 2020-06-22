type lexer = {
  originalInput: string,
  currentInput: string,
  index: int,
};

type token =
  | Int(int)
  | END;
// LPAREN
// RPAREN
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

let whitespacePattern = [%re "/^\s+/"];

let skipWhitspace = (lexer: lexer): lexer => {
  Js.log("For whitspace");
  let result: option(array(Js.String.t)) =
    Js.String.match(whitespacePattern, lexer.currentInput);
  Js.log(result);
  switch (result) {
  | Some(array) =>
    Js.log("****** got whitespace");
    Js.log(array);
    let stringToSkip = array[0];
    skipCharacters(lexer, stringToSkip);
  | _ => lexer
  };
};

let intPattern = [%re "/^(\d+)/"];

let nextTokenFrom = (lexer: lexer): (token, lexer) => {
  // let match = current |> Js.String.match(intPattern);

  Js.log("****** Huhu " ++ lexer.currentInput);

  let lexer = skipWhitspace(lexer);

  Js.log("about to match on" ++ lexer.currentInput);
  let whitespaceResult: option(array(Js.String.t)) =
    Js.String.match(intPattern, lexer.currentInput);
  Js.log(whitespaceResult);
  switch (whitespaceResult) {
  | Some(array) =>
    Js.log("****** got string");
    Js.log(array);
    let digits = array[0];
    let token: token = Int(int_of_string(digits));
    let nextLexer: lexer = skipCharacters(lexer, digits);
    (token, nextLexer);
  | _ =>
    Js.log("****** END");
    (END, lexer);
  };
};

let nextToken = (lexer: lexer): (token, lexer) =>
  if (String.length(lexer.currentInput) == 0) {
    (END, lexer);
  } else {
    nextTokenFrom(lexer);
  };