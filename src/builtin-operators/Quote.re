open AST;
open ArgumentsError;

let quote: operatorFunction =
  (argumentList: list(node), _environment) => {
    let length = List.length(argumentList);
    if (length !== 1) {
      raise(ArgumentsError("Expected exactly 1 argument"));
    };
    // The result of "quote" is the unquoted text:
    List.nth(argumentList, 0);
  };

let operator: node = BuiltinOperator("quote", quote, SpecialForm);