type operatorType =
  | Function
  | SpecialForm;

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

and operatorFunction = (list(node), environment) => node;