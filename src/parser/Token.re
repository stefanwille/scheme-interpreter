type token =
  | LPAREN
  | RPAREN
  | INT(int)
  | STRING(string)
  | SYMBOL(string)
  | END;

let stringOfToken = (token: token): string => {
  switch (token) {
  | LPAREN => "("
  | RPAREN => ")"
  | INT(i) => "INT(" ++ string_of_int(i) ++ ")"
  | STRING(s) => "STRING(" ++ s ++ ")"
  | SYMBOL(name) => "SYMBOL(" ++ name ++ ")"
  | END => "END"
  };
};