open StringUtil;
open AST;

let rec stringOfNode = (node: node): string =>
  switch (node) {
  | Int((i: int)) => string_of_int(i)
  | String(s) => "\"" ++ s ++ "\""
  | Boolean(b) => b ? "true" : "false"
  | Symbol(name) => name
  | BuiltinOperator(name, _, _) => "<builtin:" ++ name ++ ">"
  | CompoundOperator(parameterNames, body, _environment, _operatorType) =>
    "[lambda:("
    ++ join(parameterNames, " ")
    ++ ") "
    ++ stringOfNode(body)
    ++ "]"
  | List(list) => stringOfNodeList(list)
  | Nil => "nil"
  }

and stringOfNodeList = (list: list(node)): string =>
  stringOfList(List.map(stringOfNode, list));