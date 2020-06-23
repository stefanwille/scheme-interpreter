open AST;
open ArgumentsError;

let beginOperator: operatorFunction =
  (argumentList: list(node), _environment) => {
    let length = List.length(argumentList);
    if (length === 0) {
      raise(ArgumentsError("at least one argument is required"));
    };
    // The result of "begin" is the evaluated last argument
    List.nth(argumentList, length - 1);
  };

let operator: node = BuiltinOperator("begin", beginOperator, Function);