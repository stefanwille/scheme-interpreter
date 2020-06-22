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
let intPattern = [%re "/(0-9)+/"];

let nextTokenFrom = (lexer: lexer): (token, lexer) => {
  let currentInput =
    String.sub(
      lexer.input,
      lexer.index,
      String.length(lexer.input) - lexer.index,
    );

  Js.log("current " ++ currentInput);

  // let match = current |> Js.String.match(intPattern);
  let nextChar = currentInput.[0];
  switch (nextChar) {
  | '0' => Js.log("Int")
  | _ => Js.log("other")
  };

  (Int(123), {input: lexer.input, index: 2});
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