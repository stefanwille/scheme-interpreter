open StringUtil;
open Node;

let rec stringOfNode = (node: node): string =>
  switch (node) {
  | Int((i: int)) => string_of_int(i)
  | String(s) => "\"" ++ s ++ "\""
  | Boolean(b) => b ? "true" : "false"
  | Symbol(name) => name
  | Assignment(name, valueExpression) =>
    stringOfList(["set!", name, stringOfNode(valueExpression)])
  | Sequence(list) =>
    stringOfList(["begin", ...List.map(stringOfNode, list)])
  | BuiltinFunction(name, _) => "<#" ++ name ++ ">"
  | Quote(node) => stringOfList(["quote", stringOfNode(node)])
  | List(list) => stringOfNodeList(list)
  | Nil => "nil"
  }

and stringOfNodeList = (list: list(node)): string =>
  stringOfList(List.map(stringOfNode, list));