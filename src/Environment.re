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