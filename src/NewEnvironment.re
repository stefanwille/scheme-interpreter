open Node;
open Environment;

let defineBuiltinFunction =
    (
      environment: environment,
      name: string,
      builtinFunction: operatorFunction,
    ) => {
  setVariableValue(
    environment,
    name,
    BuiltinFunction(name, builtinFunction),
  );
};

let defineSpecialForm =
    (
      environment: environment,
      name: string,
      builtinFunction: operatorFunction,
    ) => {
  setVariableValue(environment, name, SpecialForm(name, builtinFunction));
};

let newEnvironment = (): environment => {
  let env: environment = {frame: Js.Dict.empty(), parent: None};
  defineBuiltinFunction(env, "head", BuiltinFunctions.head);
  defineBuiltinFunction(env, "+", BuiltinFunctions.plus);
  defineSpecialForm(env, "if", BuiltinFunctions.ifFunc);

  env;
};