// An operator can either be a normal function like "map" or a special form like "define".
type operatorType =
  | Function
  | SpecialForm;

// An AST node
type node =
  | Int(int)
  | String(string)
  | Boolean(bool)
  | Symbol(string)
  | BuiltinOperator(string, operatorFunction, operatorType)
  | CompoundOperator(list(string), node, environment, operatorType)
  | List(list(node))
  | Nil

and environment = {
  frame: Js.Dict.t(node),
  parent: option(environment),
}

// A builtin operator
and operatorFunction = (list(node), environment) => node;