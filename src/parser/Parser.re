open Node;
open SyntaxError;
open Lexer;

let rec parseRParen = (lexer: lexer): lexer => {
  let (token, lexer) = nextToken(lexer);
  switch (token) {
  | Token.RPAREN => lexer
  | _ =>
    raise(SyntaxError("Expected ')', got: " ++ Token.stringOfToken(token)))
  };
}

// Read list of nodes until we see an RPAREN
and parseList = (lexer: lexer): (lexer, list(node)) => {
  let peekedToken = peekNextToken(lexer);

  switch (peekedToken) {
  | Token.RPAREN =>
    let lexer = parseRParen(lexer);
    (lexer, []);
  | Token.END => raise(SyntaxError("Missing closing right parenthesis"))
  | _ =>
    let (lexer, node) = parseNode(lexer);
    let (lexer, nodes) = parseList(lexer);
    let nodes: list(node) = [node, ...nodes];
    (lexer, nodes);
  };
}

and parseNode = (lexer: lexer): (lexer, node) => {
  let (token, lexer) = nextToken(lexer);
  switch (token) {
  | Token.INT(i) => (lexer, Int(i))
  | Token.STRING(str) => (lexer, String(str))
  | Token.SYMBOL(name) => (lexer, Symbol(name))
  | Token.LPAREN =>
    let (lexer, nodes) = parseList(lexer);
    let node = List(nodes);
    (lexer, node);
  | _ =>
    raise(
      SyntaxError("Unexpected token, got: " ++ Token.stringOfToken(token)),
    )
  };
}

and parseProgram = (lexer: lexer): (lexer, list(node)) => {
  let peekedToken = peekNextToken(lexer);
  switch (peekedToken) {
  | Token.END => (lexer, [])
  | _ =>
    let (lexer, node) = parseNode(lexer);
    let (lexer, followingNodes) = parseProgram(lexer);
    (lexer, [node, ...followingNodes]);
  };
}

and parse = (input: string): list(node) => {
  let lexer = newLexer(input);
  let (_lexer, nodes) = parseProgram(lexer);
  nodes;
};