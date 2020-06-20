open Node;
open Environment;

let defineBuiltinOperator =
    (
      environment: environment,
      name: string,
      operatorFunction: operatorFunction,
      operatorType: operatorType,
    ) => {
  setVariableValue(
    environment,
    name,
    BuiltinOperator(name, operatorFunction, operatorType),
  );
};

let newEnvironment = (): environment => {
  let env: environment = makeEnvironment();
  defineBuiltinOperator(env, "head", BuiltinFunctions.head, Function);
  defineBuiltinOperator(env, "+", BuiltinFunctions.plus, Function);
  defineBuiltinOperator(env, "if", BuiltinFunctions.ifFunc, SpecialForm);
  defineBuiltinOperator(env, "begin", BuiltinFunctions.beginFunc, Function);
  defineBuiltinOperator(env, "set!", BuiltinFunctions.setFunc, SpecialForm);
  defineBuiltinOperator(env, "quote", BuiltinFunctions.quote, SpecialForm);
  defineBuiltinOperator(env, "lambda", BuiltinFunctions.lambda, SpecialForm);

  env;
};