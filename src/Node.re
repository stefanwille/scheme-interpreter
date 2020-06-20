type builtinOperatorType =
  | Function
  | SpecialForm;

type node =
  | Int(int)
  | String(string)
  | Boolean(bool)
  | Symbol(string)
  | BuiltinOperator(string, operatorFunction, builtinOperatorType)
  | CompoundOperator(list(string), node, environment, builtinOperatorType)
  | List(list(node))
  | Nil

and environment = {
  frame: Js.Dict.t(node),
  parent: option(environment),
}

and operatorFunction = (list(node), environment) => node;