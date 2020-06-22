type lexer = {
  input: string,
  index: int,
};

type token =
  | Int(int)
  | END;
// LPAREN
// RPAREN
// STRING
// SYMBOL

let newLexer = (input: string): lexer => {input, index: 0};

let whitespacePattern = [%re "/\s+/"];
let intPattern = [%re "/^\s*(\d+)/"];

let nextTokenFrom = (lexer: lexer): (token, lexer) => {
  let currentInput =
    String.sub(
      lexer.input,
      lexer.index,
      String.length(lexer.input) - lexer.index,
    );

  // let match = current |> Js.String.match(intPattern);

  Js.log("****** Huhu");

  Js.log("current " ++ currentInput);

  let result: option(array(Js.String.t)) =
    Js.String.match(intPattern, currentInput);
  Js.log(result);
  switch (result) {
  | Some(array) =>
    Js.log("****** got string");
    Js.log(array);
    let token: token = Int(int_of_string(array[1]));
    let nextLexer: lexer = {
      input: lexer.input,
      index: String.length(lexer.input),
    };
    (token, nextLexer);
  | _ =>
    Js.log("****** END");
    (END, {input: lexer.input, index: String.length(lexer.input)});
  };
};

let nextToken = (lexer: lexer): (token, lexer) => {
  let endIndex = String.length(lexer.input);
  if (lexer.index >= endIndex) {
    let nextLexer: lexer = {input: lexer.input, index: endIndex};
    (END, nextLexer);
  } else {
    nextTokenFrom(lexer);
  };
};