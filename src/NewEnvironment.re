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
  defineBuiltinOperator(env, "head", BuiltinOperators.head, Function);
  defineBuiltinOperator(env, "+", BuiltinOperators.plus, Function);
  defineBuiltinOperator(env, "if", BuiltinOperators.ifOperator, SpecialForm);
  defineBuiltinOperator(
    env,
    "begin",
    BuiltinOperators.beginOperator,
    Function,
  );
  defineBuiltinOperator(
    env,
    "set!",
    BuiltinOperators.setOperator,
    SpecialForm,
  );
  defineBuiltinOperator(env, "quote", BuiltinOperators.quote, SpecialForm);
  defineBuiltinOperator(env, "lambda", BuiltinOperators.lambda, SpecialForm);

  env;
};