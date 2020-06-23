open AST;
open ArgumentsError;
open Eval;

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

let operator: node = BuiltinOperator("set!", setOperator, SpecialForm);