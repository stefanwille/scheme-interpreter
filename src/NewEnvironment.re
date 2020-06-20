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

  defineBuiltinOperator(env, "head", Head.head, Function);
  defineBuiltinOperator(env, "+", Plus.plus, Function);
  defineBuiltinOperator(env, "if", If.ifOperator, SpecialForm);
  defineBuiltinOperator(env, "begin", Begin.beginOperator, Function);
  defineBuiltinOperator(env, "set!", Set.setOperator, SpecialForm);
  defineBuiltinOperator(env, "quote", Quote.quote, SpecialForm);
  defineBuiltinOperator(env, "lambda", Lambda.lambda, SpecialForm);

  env;
};