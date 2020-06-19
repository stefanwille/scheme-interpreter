type node =
  | Int(int)
  | Quote(node)
  | String(string)
  | Boolean(bool)
  | Symbol(string)
  | Assignment(string, node)
  | Sequence(list(node))
  | List(list(node))
  | Nil;

type environment = {
  frame: Js.Dict.t(node),
  parent: option(environment),
};

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

let rec eval = (expression: node, environment: environment): node =>
  switch (expression) {
  | Int(_) => expression
  | String(_) => expression
  | Boolean(_) => expression
  | Symbol(name) => lookupVariableValue(environment, name)
  | Assignment(name, valueExpression) =>
    evalAssignment(name, valueExpression, environment)
  | Sequence(list) => evalSequence(list, environment)
  | Quote(node) => node
  // TODO
  | List(_) => expression
  | Nil => expression
  }

and evalAssignment =
    (name: string, valueExpression: node, environment: environment): node => {
  let value = eval(valueExpression, environment);
  Js.Dict.set(environment.frame, name, value);
  String("OK");
}

and evalSequence = (list: list(node), environment: environment): node => {
  switch (list) {
  | [] => Nil
  | [lastExpression] => eval(lastExpression, environment)
  | [firstExpression, ...rest] =>
    let _ = eval(firstExpression, environment);
    evalSequence(rest, environment);
  };
};

let myEnvironment: environment = {frame: Js.Dict.empty(), parent: None};
Js.Dict.set(myEnvironment.frame, "name", Int(123));

let join = (list: list(string), separator) =>
  List.fold_left(
    (sum: string, s: string) =>
      switch (sum) {
      | "" => s
      | _ => sum ++ separator ++ s
      },
    "",
    list,
  );

let stringOfList = (list: list(string)): string => {
  let joined = join(list, " ");
  "(" ++ joined ++ ")";
};

let rec stringOfNode = (node: node): string =>
  switch (node) {
  | Int((i: int)) => string_of_int(i)
  | String(s) => "\"" ++ s ++ "\""
  | Boolean(b) => b ? "true" : "false"
  | Symbol(name) => name
  | Assignment(name, valueExpression) =>
    stringOfList(["set!", name, stringOfNode(valueExpression)])
  | Sequence(list) =>
    stringOfList(["begin", ...List.map(stringOfNode, list)])
  | Quote(node) => stringOfList(["quote", stringOfNode(node)])
  | List(list) => stringOfNodeList(list)
  | Nil => "nil"
  }

and stringOfNodeList = (list: list(node)): string =>
  stringOfList(List.map(stringOfNode, list));

let input =
  Quote(
    List([
      Int(123),
      String("Hello!"),
      Boolean(true),
      Quote(String("Hello")),
      List([]),
      Symbol("name"),
      Assignment("counter", Int(0)),
      Sequence([Int(1), Int(2)]),
      Nil,
    ]),
  );
Js.log("input: " ++ stringOfNode(input));
Js.log("Eval: " ++ stringOfNode(eval(input, myEnvironment)));
Js.log(
  "Eval: "
  ++ stringOfNode(eval(Assignment("counter", Int(3)), myEnvironment)),
);
Js.log(
  "Eval: "
  ++ stringOfNode(eval(Sequence([Int(2), Int(3)]), myEnvironment)),
);
Js.log(
  "Eval: " ++ stringOfNode(eval(Quote(Quote(List([]))), myEnvironment)),
);