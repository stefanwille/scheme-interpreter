open Node;
open ArgumentsError;
open StringOfNode;
open Eval;

let head: operatorFunction =
  (argumentList: list(node), _environment) =>
    switch (argumentList) {
    | [List(list)] => List.hd(list)
    | _ => raise(ArgumentsError("Expected exactly 1 argument"))
    };

let plus: operatorFunction =
  (argumentList: list(node), _environment) => (
    {
      let intOfNode = (summand: node) => {
        switch (summand) {
        | Int(value) => value
        | _ => raise(ArgumentsError("Not an int"))
        };
      };

      let summands: list(int) = List.map(intOfNode, argumentList);
      let sum = List.fold_left((x, y) => x + y, 0, summands);
      Int(sum);
    }: node
  );

let isTruthy = (node: node): bool =>
  switch (node) {
  | Boolean(false) => false
  | Nil => false
  | List([]) => false
  | _ => true
  };

let evalIf = (condition, consequent, alternative, environment) => {
  let evaledCondition = eval(condition, environment);
  isTruthy(evaledCondition)
    ? eval(consequent, environment) : eval(alternative, environment);
};

let ifOperator: operatorFunction =
  (argumentList: list(node), environment) => {
    switch (argumentList) {
    | [] => raise(ArgumentsError("Missing if condition and consequent"))
    | [condition, consequent, alternative] =>
      evalIf(condition, consequent, alternative, environment)
    | [condition, consequent] =>
      evalIf(condition, consequent, Nil, environment)
    | _ =>
      raise(
        ArgumentsError(
          "Too many arguments for if: " ++ stringOfNodeList(argumentList),
        ),
      )
    };
  };

let beginOperator: operatorFunction =
  (argumentList: list(node), _environment) => {
    let length = List.length(argumentList);
    if (length === 0) {
      raise(ArgumentsError("at least one argument is required"));
    };
    // The result of "begin" is the evaluated last argument
    List.nth(argumentList, length - 1);
  };

let setOperator: operatorFunction =
  (argumentList: list(node), environment) => {
    switch (argumentList) {
    | [Symbol(name), valueExpression] =>
      let value = eval(valueExpression, environment);
      Environment.setVariableValue(environment, name, value);
      String("OK");
    | _ => raise(ArgumentsError("Expected exactly 2 arguments"))
    };
  };