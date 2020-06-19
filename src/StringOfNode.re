open StringUtil;
open Node;

let rec stringOfNode = (node: node): string =>
  switch (node) {
  | Int((i: int)) => string_of_int(i)
  | String(s) => "\"" ++ s ++ "\""
  | Boolean(b) => b ? "true" : "false"
  | Symbol(name) => name
  | BuiltinOperator(name, _, _) => "<builtin:" ++ name ++ ">"
  | Quote(node) => stringOfList(["quote", stringOfNode(node)])
  | List(list) => stringOfNodeList(list)
  | Nil => "nil"
  }

and stringOfNodeList = (list: list(node)): string =>
  stringOfList(List.map(stringOfNode, list));