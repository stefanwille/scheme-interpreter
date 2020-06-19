open Node;
open StringOfNode;


exception NotAProducedure;
exception ArgumentsError(string);

let rec eval = (expression: node, environment: environment): node =>
  switch (expression) {
  | Int(_) => expression
  | String(_) => expression
  | Boolean(_) => expression
  | Symbol(name) => Environment.lookupVariableValue(environment, name)
  | Assignment(name, valueExpression) =>
    evalAssignment(name, valueExpression, environment)
  | Sequence(list) => evalSequence(list, environment)
  | Quote(node) => node
  | BuiltinFunction(_name, _function) => expression
  // TODO
  | List(list) => evalApplication(list, environment)
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
}

and evalApplication = (list: list(node), environment: environment): node =>
  switch (list) {
  | [] => raise(ArgumentsError("Missing operator"))
  | [operatorExpression, ...argumentExpressionList] =>
    let operator = eval(operatorExpression, environment);
    let argumentList =
      List.map(
        argumentExpression => eval(argumentExpression, environment),
        argumentExpressionList,
      );
    Js.log("evalApplication " ++ stringOfNode(operator));
    apply(operator, argumentList, environment);
  }

and apply =
    (operator: node, argumentList: list(node), environment: environment)
    : node =>
  switch (operator) {
  | BuiltinFunction(_name, operatorFunction) =>
    operatorFunction(argumentList, environment)
  | _ =>
    Js.log("Got: " ++ stringOfNode(operator));
    raise(NotAProducedure);
  };

let builtinFunctionHead: operatorFunction =
  (argumentList, _environment) =>
    switch (argumentList) {
    | [] => raise(ArgumentsError("Missing list"))
    | [List(list)] => List.hd(list)
    | _ => raise(ArgumentsError("Too many arguments"))
    };

let myEnvironment: environment = {frame: Js.Dict.empty(), parent: None};
Js.Dict.set(myEnvironment.frame, "name", Int(123));
Js.Dict.set(
  myEnvironment.frame,
  "head",
  BuiltinFunction("head", builtinFunctionHead),
);

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
  ) /* Js.log("Eval: " ++ stringOfNode(evaledApply))*/ /*   "Eval: */ /* )*/ /*   "Eval: " ++ stringOfNode(eval(Quote(Quote(List([]))), myEnvironment))*/ /* let evaledApply */ /*     List([Symbol("head"), String("one"), String("two")])*/ /*   )*/ /*     myEnvironment*/ /*   eval*/ /* )*/ /* Js.log*/ /*   ++ stringOfNode(eval(Sequence([Int(2), Int(3)]), myEnvironment))*/;
// Js.log("input: " ++ stringOfNode(input));
// Js.log("Eval: " ++ stringOfNode(eval(input, myEnvironment)));
// Js.log(
//   "Eval: "
//   ++ stringOfNode(eval(Assignment("counter", Int(3)), myEnvironment)),
// );
// Js.log(