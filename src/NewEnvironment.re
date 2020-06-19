open Node;
open Environment;

let defineBuiltinOperator =
    (
      environment: environment,
      name: string,
      operatorFunction: operatorFunction,
      operatorType: builtinOperatorType,
    ) => {
  setVariableValue(
    environment,
    name,
    BuiltinOperator(name, operatorFunction, operatorType),
  );
};

let newEnvironment = (): environment => {
  let env: environment = {frame: Js.Dict.empty(), parent: None};
  defineBuiltinOperator(env, "head", BuiltinFunctions.head, Function);
  defineBuiltinOperator(env, "+", BuiltinFunctions.plus, Function);
  defineBuiltinOperator(env, "if", BuiltinFunctions.ifFunc, SpecialForm);
  defineBuiltinOperator(env, "begin", BuiltinFunctions.beginFunc, Function);

  env;
};