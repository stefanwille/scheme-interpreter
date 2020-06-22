open Node;
open Environment;
open ArgumentsError;

let makeEnvironmentWith = (builtinOperators: list(node)) => {
  let env = makeEnvironment();
  let defineBuiltinOperator = (node: node) => {
    switch (node) {
    | BuiltinOperator(name, _operatorFunction, _operatorType) =>
      setVariableValue(env, name, node)
    | _ => raise(ArgumentsError("Not a BuiltinOperator"))
    };
  };

  List.iter(defineBuiltinOperator, builtinOperators);
  env;
};

let builtins: list(node) = [
  Head.operator,
  Tail.operator,
  Plus.operator,
  If.operator,
  Begin.operator,
  Set.operator,
  Quote.operator,
  Lambda.operator,
];

let newEnvironment = (): environment => {
  makeEnvironmentWith(builtins);
};