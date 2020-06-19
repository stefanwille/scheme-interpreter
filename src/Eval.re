open Node;
open ArgumentsError;

exception NotAnOperator;

let rec eval = (expression: node, environment: environment): node =>
  switch (expression) {
  | Int(_) => expression
  | String(_) => expression
  | Boolean(_) => expression
  | Symbol(name) => Environment.lookupVariableValue(environment, name)
  | Assignment(name, valueExpression) =>
    evalAssignment(name, valueExpression, environment)
  | Quote(node) => node
  | BuiltinOperator(_name, _function, _type) => expression
  | List(list) => evalApplication(list, environment)
  | Nil => expression
  }

and evalAssignment =
    (name: string, valueExpression: node, environment: environment): node => {
  let value = eval(valueExpression, environment);
  Js.Dict.set(environment.frame, name, value);
  String("OK");
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
  | BuiltinOperator(_name, operatorFunction, operatorType) =>
    applyBuiltinOperator(
      operatorFunction,
      operatorType,
      argumentList,
      environment,
    )
  | _ => raise(NotAnOperator)
  }

and applyBuiltinOperator =
    (
      operatorFunction: operatorFunction,
      operatorType: builtinOperatorType,
      argumentList: list(node),
      environment: environment,
    )
    : node => {
  let usedArgumentList =
    switch (operatorType) {
    | Function =>
      List.map(argument => eval(argument, environment), argumentList)
    | SpecialForm => argumentList
    };

  operatorFunction(usedArgumentList, environment);
};