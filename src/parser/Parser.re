open AST;
open SyntaxError;
open Lexer;

/*
 Grammar used for this parser:

 Program ::=  Node* END;
 Node ::= INT | STRING | SYMBOL | (LPAREN List);
 List ::= Node* RPAREN;
 */

let rec parseRParen = (lexer: lexer): lexer => {
  let lexer = nextToken(lexer);
  switch (lexer.token) {
  | Token.RPAREN => lexer
  | _ =>
    raise(
      SyntaxError("Expected ')', got: " ++ Token.stringOfToken(lexer.token)),
    )
  };
}

// Read list of nodes until we see an RPAREN
and parseList = (lexer: lexer): (lexer, list(node)) => {
  let lexer = ref(lexer);
  let nodes = ref([]);
  let break = ref(false);

  while (! break^) {
    let peekedToken = peekNextToken(lexer^);

    switch (peekedToken) {
    | Token.RPAREN =>
      lexer := parseRParen(lexer^);
      break := true;
    | _ =>
      let (nextLexer, node) = parseNode(lexer^);
      lexer := nextLexer;
      nodes := List.append(nodes^, [node]);
    };
  };

  (lexer^, nodes^);
}

and parseNode = (lexer: lexer): (lexer, node) => {
  let lexer = nextToken(lexer);
  switch (lexer.token) {
  | Token.INT(i) => (lexer, Int(i))
  | Token.STRING(str) => (lexer, String(str))
  | Token.SYMBOL(name) => (lexer, Symbol(name))
  | Token.LPAREN =>
    let (lexer, nodes) = parseList(lexer);
    let node = List(nodes);
    (lexer, node);
  | _ =>
    raise(
      SyntaxError(
        "Unexpected token, got: " ++ Token.stringOfToken(lexer.token),
      ),
    )
  };
}

and parseProgram = (lexer: lexer): list(node) => {
  let lexer = ref(lexer);
  let break = ref(false);
  let nodes = ref([]);

  while (! break^) {
    let peekedToken = peekNextToken(lexer^);

    switch (peekedToken) {
    | Token.END => break := true
    | _ =>
      let (newLexer, node) = parseNode(lexer^);
      nodes := List.append(nodes^, [node]);
      lexer := newLexer;
    };
  };

  nodes^;
}

and parse = (input: string): list(node) => {
  let lexer = newLexer(input);
  parseProgram(lexer);
};