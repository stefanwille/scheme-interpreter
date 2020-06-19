open Node;
open NotFoundError;

let rec lookupVariableValue = (environment: environment, name: string): node => {
  let value = Js.Dict.get(environment.frame, name);
  switch (value) {
  | Some(node) => node
  | None =>
    switch (environment.parent) {
    | Some(parent) => lookupVariableValue(parent, name)
    | None => raise(NotFoundError(name))
    }
  };
};

let setVariableValue = (environment: environment, name: string, value: node) => {
  Js.Dict.set(environment.frame, name, value);
};

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