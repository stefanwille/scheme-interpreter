open Node;
open Environment;
open ArgumentsError;

let makeEnvironmentWith =
    (builtinOperators: list(node), builtinNames: list((string, node))) => {
  let env = makeEnvironment();

  let defineBuiltinOperator = (node: node) => {
    switch (node) {
    | BuiltinOperator(name, _operatorFunction, _operatorType) =>
      setVariableValue(env, name, node)
    | _ => raise(ArgumentsError("Not a BuiltinOperator"))
    };
  };
  List.iter(defineBuiltinOperator, builtinOperators);

  let defineBuiltinName = ((name: string, node: node)) =>
    setVariableValue(env, name, node);
  List.iter(defineBuiltinName, builtinNames);

  env;
};

let builtinOperators: list(node) = [
  Head.operator,
  Tail.operator,
  Plus.operator,
  If.operator,
  Begin.operator,
  Set.operator,
  Quote.operator,
  Lambda.operator,
];

let builtinNames: list((string, node)) = [
  ("true", Boolean(true)),
  ("false", Boolean(false)),
  ("nil", Nil),
];

let newEnvironment = (): environment => {
  makeEnvironmentWith(builtinOperators, builtinNames);
};