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

let truthy = (node: node): bool =>
  switch (node) {
  | Boolean(false) => false
  | Nil => false
  | List([]) => false
  | _ => true
  };

let ifFunc: operatorFunction =
  (argumentList: list(node), environment) => {
    switch (argumentList) {
    | [] => raise(ArgumentsError("Missing if condition and consequent"))
    // TODO: if with 1 argument
    | [condition, consequent, alternative] =>
      let evaledCondition = eval(condition, environment);
      truthy(evaledCondition)
        ? eval(consequent, environment) : eval(alternative, environment);
    | _ =>
      raise(
        ArgumentsError(
          "Too many arguments for if: " ++ stringOfNodeList(argumentList),
        ),
      )
    };
  };

let beginFunc: operatorFunction =
  (argumentList: list(node), _environment) => {
    let length = List.length(argumentList);
    if (length === 0) {
      raise(ArgumentsError("at least one argument is required"));
    };
    // Return the last argument as result
    List.nth(argumentList, length - 1);
  };

let setFunc: operatorFunction =
  (argumentList: list(node), environment) => {
    switch (argumentList) {
    | [Symbol(name), valueExpression] =>
      let value = eval(valueExpression, environment);
      Environment.setVariableValue(environment, name, value);
      String("OK");
    | _ => raise(ArgumentsError("Expected exactly 2 arguments"))
    };
  };

let quote: operatorFunction =
  (argumentList: list(node), _environment) => {
    let length = List.length(argumentList);
    if (length !== 1) {
      raise(ArgumentsError("exactly 1 argument is required"));
    };
    // Quoted text:
    List.nth(argumentList, 0);
  };

let lambda: operatorFunction =
  (argumentList: list(node), environment) => {
    switch (argumentList) {
    | [List(parameterList), body] =>
      let parameterNames: list(string) =
        List.map(
          parameter =>
            switch (parameter) {
            | Symbol(name) => name
            | _ => raise(ArgumentsError("Parameter is not a symbol"))
            },
          parameterList,
        );
      CompoundOperator(parameterNames, body, environment, Function);
    | _ => raise(ArgumentsError("Exactly 2 arguments expected"))
    };
  };