type nodeType =
  | Int(int)
  | String(string)
  | Variable(string)
  | List(list(nodeType))
  | Nil;

type environment = {
  frame: Js.Dict.t(nodeType),
  parent: option(environment),
};

let rec environmentLookup = (environment: environment, name: string): nodeType => {
  let value = Js.Dict.get(environment.frame, name);
  switch (value) {
  | Some(node) => node
  | None =>
    switch (environment.parent) {
    | Some(parent) => environmentLookup(parent, name)
    | None => raise(Not_found)
    }
  };
};

let eval = (expression, environment): nodeType =>
  switch (expression) {
  | Int(_) => expression
  | String(_) => expression
  | List(l) => expression
  | Nil => expression
  | Variable(name) => environmentLookup(environment, name)
  };

let myEnvironment: environment = {frame: Js.Dict.empty(), parent: None};
Js.Dict.set(myEnvironment.frame, "name", Int(123));

let join = (list: list(string)) =>
  List.fold_left(
    (current: string, s: string) =>
      switch (current) {
      | "" => s
      | _ => current ++ ", " ++ s
      },
    "",
    list,
  );

let rec toString = (node: nodeType): string =>
  switch (node) {
  | Int(i) => string_of_int(i)
  | String(s) => s
  | List(l) => "(" ++ join(List.map(toString, l)) ++ ")"
  | Variable(v) => v
  | Nil => "nil"
  };

let result =
  eval(
    List([Int(123), String("Hello"), List([]), Variable("name"), Nil]),
    myEnvironment,
  );
Js.log("Eval: " ++ toString(result));