open AST;
open SyntaxError;
open Lexer;

/*
 Grammar used for this parser:

 Program ::=  Node* END;
 Node ::= INT | STRING | SYMBOL | List;
 List ::= LPAREN Node* RPAREN;
 */

let rec parseLParen = (lexer: lexer): lexer => {
  let lexer = nextToken(lexer);
  switch (lexer.token) {
  | Token.LPAREN => lexer
  | _ =>
    raise(
      SyntaxError("Expected '(', got: " ++ Token.stringOfToken(lexer.token)),
    )
  };
}

and parseRParen = (lexer: lexer): lexer => {
  let lexer = nextToken(lexer);
  switch (lexer.token) {
  | Token.RPAREN => lexer
  | _ =>
    raise(
      SyntaxError("Expected ')', got: " ++ Token.stringOfToken(lexer.token)),
    )
  };
}

and parseList = (lexer: lexer): (lexer, node) => {
  let lexer = parseLParen(lexer);
  let (lexer, nodes) = parseNodesUntilRParen(lexer);
  let lexer = parseRParen(lexer);

  let node = List(nodes);
  (lexer, node);
}

// Parses nodes until we meet an RPAREN
and parseNodesUntilRParen = (lexer: lexer): (lexer, list(node)) => {
  let lexer = ref(lexer);
  let nodes = ref([]);
  let break = ref(false);

  while (! break^) {
    let peekedToken = peekNextToken(lexer^);

    switch (peekedToken) {
    | Token.RPAREN => break := true
    | _ =>
      let (nextLexer, node) = parseNode(lexer^);
      lexer := nextLexer;
      nodes := List.append(nodes^, [node]);
    };
  };

  (lexer^, nodes^);
}

and parseNode = (lexer: lexer): (lexer, node) => {
  let originalLexer = lexer;
  let lexer = nextToken(lexer);
  switch (lexer.token) {
  | Token.INT(i) => (lexer, Int(i))
  | Token.STRING(str) => (lexer, String(str))
  | Token.SYMBOL(name) => (lexer, Symbol(name))
  | Token.LPAREN => parseList(originalLexer)
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