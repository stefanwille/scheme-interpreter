type node =
  | Int(int)
  | Quote(node)
  | String(string)
  | Boolean(bool)
  | Symbol(string)
  | Assignment(string, node)
  | Sequence(list(node))
  | BuiltinFunction(string, operatorFunction)
  | List(list(node))
  | Nil

and environment = {
  frame: Js.Dict.t(node),
  parent: option(environment),
}

and operatorFunction = (list(node), environment) => node;