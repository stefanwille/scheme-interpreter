open Node;

let rec lookupVariableValue = (environment: environment, name: string): node => {
  let value = Js.Dict.get(environment.frame, name);
  switch (value) {
  | Some(node) => node
  | None =>
    switch (environment.parent) {
    | Some(parent) => lookupVariableValue(parent, name)
    | None => raise(Not_found)
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

let newEnvironment = (): environment => {
  let env: environment = {frame: Js.Dict.empty(), parent: None};
  setVariableValue(env, "name", Int(123));
  defineBuiltinFunction(env, "head", BuiltinFunctions.head);
  env;
};