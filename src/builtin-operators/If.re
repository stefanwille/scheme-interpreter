open AST;
open ArgumentsError;
open StringOfNode;
open Eval;

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

let operator: node = BuiltinOperator("if", ifOperator, SpecialForm);