open AST;
open NotFoundError;
open ArgumentsError;

let makeEnvironment = (): environment => {
  frame: Js.Dict.empty(),
  parent: None,
};

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

let defineVariable = (environment: environment, name: string, value: node) => {
  Js.Dict.set(environment.frame, name, value);
};

let defineVariables =
    (environment: environment, parameters: list(string), values: list(node))
    : unit => {
  if (List.length(parameters) !== List.length(values)) {
    raise(ArgumentsError("parameters and values must have the same length"));
  };
  List.iter2(defineVariable(environment), parameters, values);
};

let extendEnvironment =
    (environment: environment, parameters: list(string), values: list(node))
    : environment => {
  let newEnvironment: environment = {
    frame: Js.Dict.empty(),
    parent: Some(environment),
  };
  defineVariables(newEnvironment, parameters, values);
  newEnvironment;
};