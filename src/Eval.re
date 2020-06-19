open Node;
open StringOfNode;
open ArgumentsError;

exception NotAProducedure;

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
  | SpecialForm(_name, _function) => expression
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
  | [operatorExpression, ...argumentList] =>
    let operator = eval(operatorExpression, environment);
    apply(operator, argumentList, environment);
  }

and apply =
    (operator: node, argumentList: list(node), environment: environment)
    : node =>
  switch (operator) {
  | BuiltinFunction(_name, operatorFunction) =>
    let evaluatedArgumentList =
      List.map(argument => eval(argument, environment), argumentList);
    operatorFunction(evaluatedArgumentList, environment);
  | SpecialForm(_name, operatorFunction) =>
    operatorFunction(argumentList, environment)
  | _ =>
    Js.log("Got: " ++ stringOfNode(operator));
    raise(NotAProducedure);
  };